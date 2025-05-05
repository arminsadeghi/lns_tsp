"""
@File    :   test_c_distance_matrix.py
@Time    :   2023/09/17
@Author  :   Armin Sadeghi
@Version :   0.1
@Contact :   a6sadegh@uwaterloo.ca
@Desc    :   None
"""

from unittest import TestCase

from lns_tsp import solver_core
from lns_tsp.setup_logger import get_logger

logger = get_logger(__name__)


class TestCDistanceMatrix(TestCase):
    """Test class for the distance matrix c extension"""

    def test_set_distance_matrix(self):
        """Test the set distance matrix function"""

        logger.warning("Testing the set_distance_matrix function from C extension")

        distance_matrix = [
            [0, 1, 2, 3, 4],
            [3, 2, 1, 0, 1],
            [1, 0, 1, 2, 3],
            [2, 1, 0, 1, 2],
            [4, 3, 2, 1, 0],
        ]
        solver_core.set_distance_matrix(distance_matrix, 5)
        tour_length = solver_core.objective_value([0, 1, 2, 3, 4], 5)

        self.assertEqual(tour_length, 10)
        logger.success("Objective value calculation is correct")
        solver_core.free_distance_matrix()

    def test_free_distance_matrix(self):
        """Test that the distance matrix is freed correctly"""
        logger.warning("Testing the free_distance_matrix function from C extension")

        distance_matrix = [
            [0, 1, 2, 3, 4],
            [3, 2, 1, 0, 1],
            [1, 0, 1, 2, 3],
            [2, 1, 0, 1, 2],
            [4, 3, 2, 1, 0],
        ]
        solver_core.set_distance_matrix(distance_matrix, 5)
        solver_core.free_distance_matrix()
        logger.success("Distance matrix is freed correctly")

    def test_large_distance_matrix(self):
        """Test the set distance matrix function with a large matrix."""

        instance_dimension = 2000
        distance_matrix = [
            list(range(instance_dimension)) for _ in range(instance_dimension)
        ]
        solver_core.set_distance_matrix(distance_matrix, instance_dimension)
        _ = solver_core.objective_value(
            list(range(instance_dimension)), instance_dimension
        )
        solver_core.free_distance_matrix()
