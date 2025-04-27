"""
@File    :   logging.py
@Time    :   2023/09/17
@Author  :   Armin Sadeghi
@Version :   0.1
@Contact :   a6sadegh@uwaterloo.ca
@Desc    :   None
"""

import logging as base_logging
import time

import colorlog

# Define a new log level
SUCCESS_LEVEL_NUM = 35
base_logging.addLevelName(SUCCESS_LEVEL_NUM, "SUCCESS")


def success(self, message, *args, **kwargs):
    """Custom success method for the logger"""
    # pylint: disable=protected-access
    self._log(SUCCESS_LEVEL_NUM, message, args, **kwargs)


base_logging.Logger.success = success

# Step 1: Record the start time
start_time = time.time()


# pylint: disable=too-few-public-methods
class ElapsedTimeFormatter(colorlog.ColoredFormatter):
    """Custom formatter to add elapsed time to logs."""

    def format(self, record):
        """Add elapsed time to the record."""
        # Calculate elapsed time and add it to the record
        elapsed_time = time.time() - start_time
        record.elapsed_time = round(elapsed_time, 4)
        return super().format(record)


def get_logger(name=None):
    """Setup a logger for the package"""
    # Create a logger
    log = base_logging.getLogger(name if name else __name__)
    log.setLevel(base_logging.DEBUG)

    # Create handlers for different levels
    c_handler = base_logging.StreamHandler()
    c_handler.setLevel(base_logging.DEBUG)
    # Create formatters and add them to handlers
    c_format = ElapsedTimeFormatter(
        fmt="%(log_color)s[%(levelname)-7s][%(elapsed_time)7s][%(name)s] %(message)s%(reset)s",
        log_colors={
            "DEBUG": "cyan",
            "INFO": "white",
            "WARNING": "yellow",
            "ERROR": "red",
            "CRITICAL": "red,bg_white",
            "SUCCESS": "green",
        },
    )
    c_handler.setFormatter(c_format)

    # Add handlers to the logger
    log.addHandler(c_handler)
    return log
