"""Cheapest insertion heuristic for TSP."""

from lns_tsp import solver_core
from lns_tsp.solver_core import TSPInstance


def cheapest_insertion(
    instance: TSPInstance, tour: list, nodes_to_insert: list
) -> list:
    """Cheapest insertion insert nodes into the tour."""
    return solver_core.cheapest_insertion(
        instance, tour, len(tour), nodes_to_insert, len(nodes_to_insert)
    )
