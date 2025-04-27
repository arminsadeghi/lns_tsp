"""Twist move heuristic."""

from lns_tsp import solver_core
from lns_tsp.solver_core import TSPInstance


def twist_move(instance: TSPInstance, tour: list) -> list:
    """Twist move heuristic."""
    return solver_core.twist_move(instance, tour, len(tour))
