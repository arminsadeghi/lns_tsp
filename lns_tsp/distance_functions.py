"""
@File    :   distance_functions.py
@Time    :   2023/09/16
@Author  :   Armin Sadeghi
@Version :   0.1
@Contact :   a6sadegh@uwaterloo.ca
@Desc    :   None
"""

from math import acos, cos, pi, sqrt

EARTH_RADIUS = 6378.388


def round_to_int(number: float):
    """ceil function for float numbers"""
    return int(number + 0.5)


class Distance:
    """Distance functions for the TSP instances"""

    @staticmethod
    def euc_distance(node1, node2):
        """Euclidean distance between nodes"""
        distance_x = node1.location.x - node2.location.x
        distance_y = node1.location.y - node2.location.y
        return sqrt(distance_x**2 + distance_y**2)

    @staticmethod
    def geo_distance(node1, node2):
        """Geographical distance between nodes"""

        def convert_to_lat_lon(node):
            """converts the node to latitude and longitude"""
            deg_x = round_to_int(node.location.x)
            node.location.x = (
                pi * (deg_x + 5.0 * (node.location.x - deg_x) / 3.0) / 180.0
            )
            deg_y = round_to_int(node.location.y)
            node.location.y = (
                pi * (deg_y + 5.0 * (node.location.y - deg_y) / 3.0) / 180.0
            )

        convert_to_lat_lon(node1)
        convert_to_lat_lon(node2)
        angle_1 = cos(node1.location.y - node2.location.y)
        angle_2 = cos(node1.location.x - node2.location.x)
        angle_3 = cos(node1.location.x - node2.location.x)
        return (
            EARTH_RADIUS
            * acos(0.5 * ((1.0 + angle_1) * angle_2 - (1.0 - angle_1) * angle_3))
            + 1.0
        )

    @staticmethod
    def pseudo_euc_distance(node1, node2):
        """Pseudo euclidean distance between nodes"""

        distance_x = node1.location.x - node2.location.x
        distance_y = node1.location.y - node2.location.y
        rij = sqrt((distance_x**2 + distance_y**2) / 10.0)
        tij = round_to_int(rij)
        if tij < rij:
            return tij + 1
        return tij

    @staticmethod
    def ceil_euc_distance(node1, node2):
        """Ceil euclidean distance between nodes"""
        return round_to_int(Distance.euc_distance(node1, node2))
