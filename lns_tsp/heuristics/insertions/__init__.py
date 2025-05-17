"""All insertion heuristics for TSP."""

from lns_tsp.heuristics.insertions.cheapest_insertion import cheapest_insertion
from lns_tsp.heuristics.insertions.nearest_insertion import nearest_insertion
from lns_tsp.heuristics.insertions.random_insertion import random_insertion

__all__ = [
    "cheapest_insertion",
    "nearest_insertion",
    "random_insertion",
]
