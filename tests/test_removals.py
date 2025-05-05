"""
@File    :   test_removals.py
@Time    :   2023/09/17
@Author  :   Armin Sadeghi
@Version :   0.1
@Contact :   a6sadegh@uwaterloo.ca
@Desc    :   None
"""

from random import random
from unittest import TestCase

from lns_tsp import solver_core
from lns_tsp.heuristics.removals import random_removal, worst_removal


class TestRemovals(TestCase):
    """Tests removal heuristics"""

    def test_random_removal(self):
        """tests random removal"""
        logger.warning("Testing random removal")

        tour = [0, 1, 2, 3, 4, 5, 6, 7, 8]
        num_to_remove = 3

        new_tour, deleted_nodes = random_removal(tour, num_to_remove)

        self.assertEqual(len(new_tour), len(tour) - num_to_remove)
        logger.info("New tour: %s, deleted nodes: %s", new_tour, deleted_nodes)

    def test_worst_removal(self):
        """tests random removal"""

        logger.warning("Testing worst removal")

        tour = [0, 1, 2, 3, 4, 5, 6, 7, 8]
        num_to_remove = 3

        # 9 by 9 distance matrix
        distance_matrix = [
            [random() for _ in range(len(tour))] for __ in range(len(tour))
        ]
        solver_core.set_distance_matrix(distance_matrix, 9)

        new_tour, deleted_nodes = worst_removal(tour, num_to_remove)
        solver_core.free_distance_matrix()

        logger.info("New tour: %s, deleted nodes: %s", new_tour, deleted_nodes)
        self.assertEqual(len(new_tour), len(tour) - num_to_remove)
