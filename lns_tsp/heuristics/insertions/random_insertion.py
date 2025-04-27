"""Random insertion heuristic for TSP."""

import random


def random_insertion(tour: list, nodes_to_insert: list) -> list:
    """Randomly insert nodes into the tour."""
    for node in nodes_to_insert:
        tour.insert(random.randint(0, len(tour)), node)
    return tour
