"""
@File    :   cluster_removal.py
@Time    :   2023/09/17
@Author  :   Armin Sadeghi
@Version :   0.1
@Contact :   a6sadegh@uwaterloo.ca
@Desc    :   None
"""

from lns_tsp import solver_core
from lns_tsp.solver_core import TSPInstance


def cluster_removal(instance: TSPInstance, tour: list, num_to_remove: int) -> list:
    """Remove a random subset of nodes from the tour."""
    tour_length = len(tour)
    temp_tour = solver_core.cluster_removal(instance, tour, tour_length, num_to_remove)
    new_tour = [x for x in temp_tour if x != -1]
    deleted_nodes = [x for x in range(tour_length) if x not in new_tour]
    return new_tour, deleted_nodes
