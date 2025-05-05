"""
@File    :   test_read_tsplib.py
@Time    :   2023/09/17
@Author  :   Armin Sadeghi
@Version :   0.1
@Contact :   a6sadegh@uwaterloo.ca
@Desc    :   None
"""

import os
from unittest import TestCase

from lns_tsp.data_util import DataLoader
from lns_tsp.setup_logger import get_logger
from lns_tsp.tsp_instance import TSPInstance

logger = get_logger(__name__)

TSP_LIB_DIRECTORY = os.path.dirname(os.path.abspath(__file__))


class ReadTSPLibParse(TestCase):
    """Tests the DataLoader module"""

    def test_read_data(self):
        """tests reading the data"""
        logger.warning("Testing the read_data function")
        try:
            instance = DataLoader.read_data(TSP_LIB_DIRECTORY + "/../data/att48.tsp")
        except FileNotFoundError as e:
            logger.error(str(e))
            raise FileNotFoundError("File not found")
        # Assert that the data type is TPSInstance.
        self.assertIsInstance(instance, TSPInstance)

        self.assertEqual(instance.dimension, 48)
        self.assertEqual(instance.edge_weight_type, "ATT")
        self.assertEqual(instance.instance_name, "att48")
