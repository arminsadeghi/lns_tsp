"""TSP solver main class."""

import random
import time

from lns_tsp import solver_core
from lns_tsp.data_util import DataLoader
from lns_tsp.exceptions import InvalidTour
from lns_tsp.heuristic_selection import HeuristicChooser
from lns_tsp.heuristics.twist_move import twist_move
from lns_tsp.setup_logger import get_logger
from lns_tsp.simulated_annealing import SimulatedAnnealing
from lns_tsp.solver_config import SolverConfig
from lns_tsp.solver_core import objective_value
from lns_tsp.solver_stats import SolverStats

logger = get_logger(__name__)


# pylint: disable=attribute-defined-outside-init
# pylint: disable=too-few-public-methods
class Solver:
    """Solver class for the TSP problem."""

    def __init__(self, config: SolverConfig, instance_file_path: str):
        """Solver constructor."""
        self.instance = solver_core.load_instance(instance_file_path)
        if not self.instance:
            raise ValueError(f"Invalid instance file: {instance_file_path}")
        self.config = config
        self._simulated_annealing = SimulatedAnnealing(config)
        self._heuristic_chooser = HeuristicChooser(config)
        self.stats = SolverStats(config, self.instance)

    def run(self):
        """Run the iterations."""
        try:
            while self.stats.iterate():
                self._log_stats()
                # Choose insertion and removal heuristics.
                insertion, removal = self._heuristic_chooser.choose()
                num_vertices_to_remove = (
                    self._simulated_annealing.get_num_vertices_to_remove()
                )
                temp_tour, deleted_nodes = removal(
                    self.instance, self.stats.current_tour, num_vertices_to_remove
                )
                new_tour = insertion(self.instance, temp_tour, deleted_nodes)
                assert len(new_tour) == len(self.stats.current_tour)
                assert set(new_tour) == set(
                    self.stats.current_tour
                ), "Tour is not valid!"
                try:
                    accepted = self._update(new_tour)
                    self._heuristic_chooser.adapt_heuristic_weights(accepted)
                except InvalidTour as exc:
                    logger.error("Invalid tour found: %s", str(exc))
                    logger.info("Reverting to the best tour found!")
                    self.stats.revert_to_best_tour()
            new_tour = self._post_improvement(self.stats.get_best_tour())
            self.stats.update_best_tour(new_tour, self._get_objective_value(new_tour))
        except KeyboardInterrupt:
            return self.stats.get_best_tour()
        finally:
            self._log_final_stats()
        return self.stats.get_best_tour()

    def _update(self, new_tour):
        """Update the solution based on the new found tour."""
        new_objective_value = self._get_objective_value(new_tour)
        accepted = self._update_current_tour(new_tour, new_objective_value)
        self.stats.update_best_tour(new_tour, new_objective_value)
        self._simulated_annealing.update_temperature()
        return accepted

    def _post_improvement(self, tour):
        """Post processing of the accepted tour."""
        tour = twist_move(self.instance, tour)
        return tour

    def _update_current_tour(self, new_tour, new_objective_value):
        acceptance_probability = self._simulated_annealing.acceptance_probability(
            self.stats.current_objective_value, new_objective_value
        )
        if random.random() < acceptance_probability:
            # new_tour = self._post_improvement(new_tour)
            self.stats.update_current_tour(new_tour, new_objective_value)
            return True
        return False

    def __str__(self):
        return (
            f"SolverStats:\n\t iteration={self.stats.iteration}"
            f"\n\t current_objective_value={self.stats.current_objective_value}"
            f"\n\t best_found_obj={self.stats.best_found_obj}"
            f"\n\t iteration_since_last_improvement={self.stats.iteration_since_last_improvement}"
            f"\n\t solver_time={time.time() - self.stats.start_time}"
            f"\n\t temperature={self._simulated_annealing._temperature}"
            f"\n\t max_num_to_remove={self._simulated_annealing.get_max_num_to_remove()}"
        )

    def _log_stats(self):
        """Log solver statistics."""
        if not self.config.log:
            return
        if self.stats.iteration % self.config.log_frequency == 0:
            logger.info(self)

    def _get_objective_value(self, tour):
        """Get the current objective value."""
        return objective_value(self.instance, tour, len(tour))

    def _log_final_stats(self):
        """Log the final statistics."""
        if not self.config.log:
            return
        optimal_tour = DataLoader.read_optimal_tour(
            f"data/{self.instance.instance_name}.opt.tour"
        )
        optimal_objective_value = (
            self._get_objective_value(optimal_tour) if optimal_tour else None
        )
        logger.info("Optimal tour: %s", optimal_tour)
        logger.info(
            "Optimal objective value: %s",
            optimal_objective_value if optimal_objective_value else "N/A",
        )
        logger.info("Solver stats: %s", self)
        logger.info(
            "Optimal objective value: %s",
            optimal_objective_value if optimal_objective_value else "N/A",
        )
        logger.info("Best tour: %s", self.stats.best_tour_found)
        logger.info("Best objective value: %s", self.stats.best_found_obj)
        if optimal_objective_value:
            logger.info(
                "Optimality gap: %s %%",
                round(
                    (self.stats.best_found_obj - optimal_objective_value)
                    / optimal_objective_value
                    * 100,
                    2,
                ),
            )
