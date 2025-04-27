"""Simulated Annealing for TSP."""

import math
import random
from collections import namedtuple

CONFIG_FIELDS = [
    "initial_temperature",
    "cooling_rate",
]


class SimulatedAnnealingConfig(namedtuple("SimulatedAnnealingConfig", CONFIG_FIELDS)):
    """Simulated Annealing configuration class."""

    __slots__ = ()

    def __new__(cls, **kwargs):
        """SimulatedAnnealingConfig constructor."""
        for key in CONFIG_FIELDS:
            if key not in kwargs:
                raise KeyError(f"Missing key {key} in SimulatedAnnealingConfig")
        config = super().__new__(cls, **kwargs)
        return config


# pylint: disable=too-many-instance-attributes
class SimulatedAnnealing:
    """Simulated Annealing for TSP."""

    def __init__(self, config):
        self._max_num_to_remove = config.max_num_to_remove
        self._config = SimulatedAnnealingConfig(**config.simulated_annealing)
        self._temperature = self._config.initial_temperature

    def acceptance_probability(self, current_objective_value, new_objective_value):
        """Acceptance probability for the new solution."""
        if new_objective_value < current_objective_value:
            return 1.0
        return math.exp(
            (current_objective_value - new_objective_value) / self._temperature
        )

    def update_temperature(self):
        """Update the temperature."""
        self._temperature *= self._config.cooling_rate

    def get_max_num_to_remove(self):
        """Get the maximum number of vertices to remove."""
        return max(
            2,
            int(
                self._max_num_to_remove
                * self._temperature
                / self._config.initial_temperature
            ),
        )

    def get_num_vertices_to_remove(self):
        """Get the number of vertices to remove."""
        # return random.randint(1, max(min(num_to_remove, self._max_num_to_remove), 1))
        return random.randint(2, self.get_max_num_to_remove())
