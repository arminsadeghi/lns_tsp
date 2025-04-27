"""
@File    :   TSPinstance.py
@Time    :   2023/09/16
@Author  :   Armin Sadeghi
@Version :   0.1
@Contact :   a6sadegh@uwaterloo.ca
@Desc    :   None
"""

import random

from lns_tsp.distance_functions import Distance
from lns_tsp.exceptions import InvalidDistanceFunctionType, InvalidTour


# pylint: disable=too-many-instance-attributes
class TSPInstance:
    """TSP instance class for representing the TSP instance"""

    def __init__(self):
        self.instance_name = None
        self.dimension = None
        self.nodes = []
        self.distance_matrix = []
        self.type = None
        self.edge_weight_type = None
        self.edge_weight_format = None
        self.optimal_tour = []
        self.optimal_objective_value = 0
        self.is_valid = False
        self.tour = []

    def init_dist_matrix(self):
        """initializes the distance matrix"""
        if self.dimension is None:
            raise ValueError("Dimension not set")

        for _ in range(self.dimension):
            self.distance_matrix.append([0 for _ in range(self.dimension)])

    def generate_distance_matrix(self):
        """generates the distance matrix based on the distance type"""
        self.init_dist_matrix()

        if self.dimension > 500:
            print("[WARNING] Distance matrix generation may take a while! skipping...")
            self.is_valid = False
            return
        distance_func = None
        if self.edge_weight_type == "EUC_2D":
            distance_func = Distance.euc_distance
        elif self.edge_weight_type == "GEO":
            distance_func = Distance.geo_distance
        elif self.edge_weight_type == "ATT":
            distance_func = Distance.pseudo_euc_distance
        elif self.edge_weight_type == "CEIL_2D":
            distance_func = Distance.ceil_euc_distance

        if distance_func is not None:
            self.generate_distance_matrix_(distance_func)
            self.is_valid = True
        else:
            raise InvalidDistanceFunctionType(
                f"Distance function {self.edge_weight_type} not supported"
            )

    def generate_distance_matrix_(self, dist_func):
        """generates the distance matrix based on the distance function"""
        assert self.dimension == len(
            self.nodes
        ), "Dimension and number of nodes do not match"

        for i in range(self.dimension):
            for j in range(i, self.dimension):
                self.distance_matrix[i][j] = dist_func(self.nodes[i], self.nodes[j])
                self.distance_matrix[j][i] = self.distance_matrix[i][j]

    def __repr__(self) -> str:
        return (
            f"TSP Instance:\n"
            f"\t\tName: {self.instance_name}\n"
            + f"\t\tType: {self.type}\n"
            + f"\t\tDimension: {self.dimension}\n"
            + f"\t\tEdge Weight Type: {self.edge_weight_type}\n"
            + f"\t\tEdge Weight Format: {self.edge_weight_format}\n"
            + f"\t\tOptimal Objective Value: {self.optimal_objective_value}"
        )

    def is_valid_tour(self, tour):
        """Checks if the tour is valid"""
        if len(tour) != self.dimension:
            return False

        for i in range(self.dimension):
            if i not in tour:
                print(f"[INFO] Tour does not contain node {i}")
                return False

        if len(tour) != len(set(tour)):
            print("Tour contains duplicate nodes")
            return False
        return True

    def objective_value(self, tour: list):
        """calculates the objective value of the tour"""
        if not self.is_valid_tour(tour):
            raise InvalidTour("Tour is not valid!")

        obj = 0
        for current_point, next_point in zip(tour, tour[1:] + [tour[0]]):
            obj += self.distance_matrix[current_point][next_point]
        return round(obj, 3)

    def initial_tour(self):
        """Returns the initial tour. By default it is the list of nodes"""
        return list(range(self.dimension))

    def randomized_initial_tour(self):
        """Returns a randomized initial tour"""
        tour = self.initial_tour()
        random.shuffle(tour)
        return tour
