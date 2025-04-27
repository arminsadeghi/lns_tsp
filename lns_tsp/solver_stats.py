"""Solver statistics class."""

import random
import time

from lns_tsp.setup_logger import get_logger
from lns_tsp.solver_config import SolverConfig
from lns_tsp.solver_core import TSPInstance, objective_value

logger = get_logger(__name__)


# pylint: disable=too-many-instance-attributes
class SolverStats:
    """Solver statistics class."""

    def __init__(self, config: SolverConfig, instance: TSPInstance):
        self._config: SolverConfig = config
        self.iteration = 0
        self.current_tour = [i for i in range(instance.dimension)]
        random.shuffle(self.current_tour)
        self.current_objective_value = objective_value(
            instance, self.current_tour, len(self.current_tour)
        )
        self.best_tour_found = self.current_tour
        self.best_found_obj = self.current_objective_value
        self._iteration_since_last_improvement = 0
        self._start_time = None

    def iterate(self):
        """Check if we should iterate again."""
        if self._start_time is None:
            self.start()

        if self.iteration > self._config.max_iterations:
            return False
        if self._iteration_since_last_improvement >= self._config.max_no_improvement:
            logger.warning(
                "Iteration %d, No improvements for %d iterations!",
                self.iteration,
                self._iteration_since_last_improvement,
            )
            self.revert_to_best_tour()
            self.iteration += 1
            self._iteration_since_last_improvement = 0
            return True

        current_time = time.time()
        if current_time - self._start_time > self._config.max_time:
            return False
        self.iteration += 1
        return True

    def start(self):
        """Set the start time."""
        self._start_time = time.time()

    def update_best_tour(self, new_tour, new_objective_value):
        """Update the best tour found so far."""
        if new_objective_value < self.best_found_obj:
            self.best_tour_found = new_tour
            self.best_found_obj = new_objective_value
            if self._config.log:
                logger.success(
                    "Iteration %d, New best tour found: %s",
                    self.iteration,
                    self.best_found_obj,
                )
            self._iteration_since_last_improvement = 0
        else:
            self._iteration_since_last_improvement += 1

    def update_current_tour(self, new_tour, new_objective_value):
        """Update the current tour."""
        self.current_tour = new_tour
        self.current_objective_value = new_objective_value

    def get_best_tour(self):
        """Get the best tour found so far."""
        return self.best_tour_found

    def revert_to_best_tour(self):
        """Revert the current tour to the best tour found so far."""
        self.current_tour = self.best_tour_found
        self.current_objective_value = self.best_found_obj

    @property
    def iteration_since_last_improvement(self):
        """Get the number of iterations since last improvement."""
        return self._iteration_since_last_improvement

    @property
    def start_time(self):
        """Get the start time."""
        return self._start_time
