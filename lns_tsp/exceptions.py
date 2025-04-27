"""
@File    :   Exceptions.py
@Time    :   2023/09/16
@Author  :   Armin Sadeghi
@Version :   0.1
@Contact :   a6sadegh@uwaterloo.ca
@Desc    :   None
"""


class InvalidDistanceFunctionType(Exception):
    """Exception for invalid distance function type"""

    def __init__(self, message):
        self.message = message
        super().__init__(self.message)


class InvalidTour(Exception):
    """Exception for invalid tour"""

    def __init__(self, message):
        self.message = message
        super().__init__(self.message)
