"""
@File    :   test_import_package.py
@Time    :   2023/09/16
@Author  :   Armin Sadeghi
@Version :   0.1
@Contact :   a6sadegh@uwaterloo.ca
@Desc    :   None
"""

from unittest import TestCase

from lns_tsp.setup_logger import get_logger

logger = get_logger(__name__)


class TestImport(TestCase):
    """tests importing the package and modules"""

    def test_import_modules(self):
        """tests importing the modules"""
        try:
            logger.warning("Testing the import of solver modules")
            # pylint: disable=unused-import
            # pylint: disable=import-outside-toplevel
            from lns_tsp import (
                DataLoader,
                Distance,
                InvalidDistanceFunctionType,
                InvalidTour,
                Node,
                TSPInstance,
            )
        except ImportError as exc:
            self.fail(f"Import error: {exc}")
