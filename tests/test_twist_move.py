"""
@File    :   test_twist_move.py
@Time    :   2023/10/15
@Author  :   Armin Sadeghi
@Version :   0.1
@Contact :   a6sadegh@uwaterloo.ca
@Desc    :   None
"""

from unittest import TestCase

from lns_tsp import solver_core
from lns_tsp.heuristics import twist_move
from lns_tsp.location import Location
from lns_tsp.node import Node
from lns_tsp.tsp_instance import TSPInstance


class TestTwistMoves(TestCase):
    """Tests nearest insertion heuristics"""

    def test_twist_move(self):
        """Tests twist moves."""
        logger.warning("Testing twist move")
        num_nodes = 4
        instance = TSPInstance()
        instance.dimension = num_nodes
        instance.nodes = [
            Node(
                0,
                location=Location(0, 0),
            ),
            Node(
                1,
                location=Location(0, 5),
            ),
            Node(
                2,
                location=Location(5, 5),
            ),
            Node(
                3,
                location=Location(5, 0),
            ),
        ]
        instance.edge_weight_type = "EUC_2D"
        instance.generate_distance_matrix()
        tour = [0, 2, 1, 3]
        solver_core.set_distance_matrix(instance.distance_matrix, num_nodes)
        new_tour = twist_move(tour)
        solver_core.free_distance_matrix()
        logger.info(new_tour)
