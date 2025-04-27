"""
@File    :   Node.py
@Time    :   2023/09/16
@Author  :   Armin Sadeghi
@Version :   0.1
@Contact :   a6sadegh@uwaterloo.ca
@Desc    :   None
"""

from lns_tsp.location import Location


# pylint: disable=too-few-public-methods
class Node:
    """Node class for representing the nodes in the TSP instance"""

    def __init__(self, node_id, location: Location):
        self.node_id = node_id
        self.location = location

    def __repr__(self):
        return f"Node {self.node_id} ({self.location.x}, {self.location.y})"
