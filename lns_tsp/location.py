"""
@File    :   Location.py
@Time    :   2023/09/17
@Author  :   Armin Sadeghi
@Version :   0.1
@Contact :   a6sadegh@uwaterloo.ca
@Desc    :   None
"""


# pylint: disable=too-few-public-methods
# pylint: disable=invalid-name
class Location:
    """Location class for representing the location of a node"""

    def __init__(self, x: float, y: float, z: float = 0) -> None:
        self.x = x
        self.y = y
        self.z = z

    def __repr__(self) -> str:
        return f"({self.x}, {self.y}, {self.z})"
