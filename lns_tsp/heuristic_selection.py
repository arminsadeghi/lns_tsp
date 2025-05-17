"""Heuristic selection module."""

import random

from lns_tsp.heuristics.insertions import (
    cheapest_insertion,
    nearest_insertion,
    random_insertion,
)
from lns_tsp.heuristics.removals import (
    cluster_removal,
    path_removal,
    random_removal,
    worst_removal,
)
from lns_tsp.heuristics.twist_move import twist_move

INSERTION_HEURISTICS = {
    "random_insertion": random_insertion,
    "cheapest_insertion": cheapest_insertion,
    "nearest_insertion": nearest_insertion,
}

REMOVAL_HEURISTICS = {
    "worst_removal": worst_removal,
    "random_removal": random_removal,
    "cluster_removal": cluster_removal,
    "path_removal": path_removal,
}

POST_PROCESSING_HEURISTICS = {
    "twist_move": twist_move,
}


class HeuristicChooser:
    """Heuristic chooser class."""

    def __init__(self, config):
        """HeuristicChooser constructor."""
        self.weights = {}
        self.heuristics = config.heuristics["weights"]
        self.increment = config.heuristics["increment"]
        self.removal_heuristics = []
        self.insertion_heuristics = []
        for heuristic in self.heuristics:
            if heuristic["name"].endswith("removal"):
                self.removal_heuristics.append(heuristic["name"])
                self.weights[heuristic["name"]] = heuristic["weight"]
            elif heuristic["name"].endswith("insertion"):
                self.insertion_heuristics.append(heuristic["name"])
                self.weights[heuristic["name"]] = heuristic["weight"]
            else:
                raise ValueError(f"Unknown heuristic {heuristic}")

        self._last_insertion_heuristic = None
        self._last_removal_heuristic = None

    def _total_weight(self, heuristics):
        """Return the total weight of the heuristics."""
        return sum(self.weights[heuristic] for heuristic in heuristics)

    def _choose_heuristic(self, heuristics):
        """Roulette wheel selection of the heuristic."""
        total_weight = self._total_weight(heuristics)
        random_value = random.uniform(0, total_weight)
        current_sum = 0
        for heuristic in heuristics:
            current_sum += self.weights[heuristic]
            if current_sum >= random_value:
                return heuristic
        return None

    def choose(self):
        """Choose the heuristic for the given iteration."""
        insertion_heuristic = self._choose_heuristic(self.insertion_heuristics)
        if insertion_heuristic is None:
            insertion_heuristic = random_insertion
        self._last_insertion_heuristic = insertion_heuristic

        removal_heuristic = self._choose_heuristic(self.removal_heuristics)
        if removal_heuristic is None:
            removal_heuristic = random_removal
        self._last_removal_heuristic = removal_heuristic

        return (
            INSERTION_HEURISTICS[insertion_heuristic],
            REMOVAL_HEURISTICS[removal_heuristic],
        )

    def increase_weight(self, heuristic):
        """Increase the weight of the heuristic."""
        self.weights[heuristic] += self.increment

    def decrease_weight(self, heuristic):
        """Decrease the weight of the heuristic."""
        self.weights[heuristic] -= self.increment
        if self.weights[heuristic] < 0:
            self.weights[heuristic] = 0

    def adapt_heuristic_weights(self, success):
        """Adapt the weights of the heuristics."""
        if success:
            self.decrease_weight(self._last_insertion_heuristic)
            self.decrease_weight(self._last_removal_heuristic)
        else:
            self.increase_weight(self._last_insertion_heuristic)
            self.increase_weight(self._last_removal_heuristic)
