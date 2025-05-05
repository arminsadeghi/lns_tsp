"""
@File    :   test_nearest_insertion.py
@Time    :   2023/10/15
@Author  :   Armin Sadeghi
@Version :   0.1
@Contact :   a6sadegh@uwaterloo.ca
@Desc    :   Tests the nearest insertion heuristic.
"""

import time
from random import random
from unittest import TestCase

from lns_tsp import solver_core
from lns_tsp.heuristics.insertions import cheapest_insertion, nearest_insertion
from lns_tsp.setup_logger import get_logger

logger = get_logger(__name__)


class TestInsertion(TestCase):
    """Tests nearest insertion heuristics"""

    def test_nearest_insertion(self):
        """Tests inserting with nearest insertion."""
        logger.warning("Testing nearest insertion")
        number_of_vertices = 300
        tour = list(range(200))
        nodes_to_insert = list(range(200, 300))
        # 9 by 9 distance matrix
        distance_matrix = [
            [random() for _ in range(number_of_vertices)]
            for __ in range(number_of_vertices)
        ]
        solver_core.set_distance_matrix(distance_matrix, 300)
        start_time = time.perf_counter()
        nearest_insertion(tour, nodes_to_insert)
        logger.info(
            "Nearest insertion took %s seconds", time.perf_counter() - start_time
        )
        solver_core.free_distance_matrix()

    def test_cheapest_insertion(self):
        """Tests inserting with nearest insertion."""
        logger.warning("Testing nearest insertion")
        number_of_vertices = 300
        tour = list(range(200))
        nodes_to_insert = list(range(200, 300))
        # 9 by 9 distance matrix
        distance_matrix = [
            [random() for _ in range(number_of_vertices)]
            for __ in range(number_of_vertices)
        ]
        solver_core.set_distance_matrix(distance_matrix, 300)
        start_time = time.perf_counter()
        cheapest_insertion(tour, nodes_to_insert)
        logger.info(
            "Cheapest insertion took %s seconds", time.perf_counter() - start_time
        )
        solver_core.free_distance_matrix()
