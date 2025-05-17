"""Module of all removal heuristics."""

from lns_tsp.heuristics.removals.cluster_removal import cluster_removal
from lns_tsp.heuristics.removals.path_removal import path_removal
from lns_tsp.heuristics.removals.random_removal import random_removal
from lns_tsp.heuristics.removals.worst_removal import worst_removal

__all__ = [
    "random_removal",
    "worst_removal",
    "cluster_removal",
    "path_removal",
]
