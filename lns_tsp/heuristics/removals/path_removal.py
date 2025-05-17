"""Path removal heuristic for TSP."""

import random

from lns_tsp.solver_core import TSPInstance


def path_removal(instance: TSPInstance, tour: list, num_to_remove: int) -> list:
    """Remove a segment of the tour."""
    tour_length = len(tour)
    start_index = random.randint(0, tour_length - 1)
    end_index = (start_index + num_to_remove) % tour_length
    if end_index < start_index:
        # Wrap around the tour
        removed_segment = tour[start_index:] + tour[:end_index]
        remaining_tour = tour[end_index:start_index]
    else:
        # No wrap around
        removed_segment = tour[start_index:end_index]
        remaining_tour = tour[:start_index] + tour[end_index:]
    return remaining_tour, removed_segment
