"""Regret K-Insertion Heuristic for TSP."""

from lns_tsp import solver_core
from lns_tsp.solver_core import TSPInstance


def regret_2_insertion(
    instance: TSPInstance, tour: list, nodes_to_insert: list
) -> list:
    """Regret insertion with k=2 insert nodes into the tour."""
    try:
        return solver_core.regret_insertion(
            instance, tour, len(tour), nodes_to_insert, len(nodes_to_insert), 2
        )
    except Exception as e:
        print(f"Error in regret_2_insertion: {e}")
        return tour


def regret_3_insertion(
    instance: TSPInstance, tour: list, nodes_to_insert: list
) -> list:
    """Regret insertion with k=3 insert nodes into the tour."""
    try:
        return solver_core.regret_insertion(
            instance, tour, len(tour), nodes_to_insert, len(nodes_to_insert), 3
        )
    except Exception as e:
        print(f"Error in regret_3_insertion: {e}")
        return tour
