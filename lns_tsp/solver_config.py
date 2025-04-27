"""A set of configs for the Large Neighborhood Search solver."""

import json
import os
from collections import namedtuple

from lns_tsp.setup_logger import get_logger

logger = get_logger(__name__)

SOLVER_CONFIG_FIELDS = [
    "max_iterations",
    "max_no_improvement",
    "max_time",
    "simulated_annealing",
    "max_num_to_remove",
    "heuristics",
    "log_frequency",
    "log",
    "post_processing_probability",
]

MODULE_DIRECTORY = os.path.dirname(os.path.abspath(__file__))
DEFAULT_CONFIG_FILE = MODULE_DIRECTORY + "/config/default_solver_config.json"


class SolverConfig(namedtuple("SolverConfig", SOLVER_CONFIG_FIELDS)):
    """Solver configuration class."""

    __slots__ = ()

    def __new__(cls, **kwargs):
        """SolverConfig constructor."""
        default_config = cls._read_json_config(DEFAULT_CONFIG_FILE)
        missing_keys = set(default_config.keys()) - set(kwargs.keys())
        for key in SOLVER_CONFIG_FIELDS:
            if key not in kwargs:
                kwargs[key] = default_config[key]
        if missing_keys:
            logger.warning("Missing Solver Configs: %s", missing_keys)
        config = super().__new__(cls, **kwargs)
        if config.log:
            logger.info(config)
        return config

    def __str__(self) -> str:
        res = "SolverConfig:\n"
        for key in SOLVER_CONFIG_FIELDS:
            attr = getattr(self, key)
            if isinstance(attr, dict):
                res += f"\t{key}:\n"
                for k, v in attr.items():
                    res += f"\t\t{k}: {v}\n"
            else:
                res += f"\t{key}: {attr}\n"
        return res

    @staticmethod
    def _read_json_config(config_file_name: str):
        """Reads the solver configuration from a json file."""
        if config_file_name is None:
            raise FileNotFoundError("No config file provided!")

        try:
            logger.info("Reading config file %s", config_file_name)
            if not os.path.exists(config_file_name):
                raise FileNotFoundError(f"File {config_file_name} not found")
            with open(config_file_name, "r", encoding="utf-8") as stream:
                return json.loads(stream.read())
        except FileNotFoundError as exc:
            raise FileNotFoundError("File not found") from exc

    @staticmethod
    def from_config_file(config_file_name: str):
        """Reads the solver configuration from a yaml file."""
        try:
            config = SolverConfig._read_json_config(config_file_name)
            return SolverConfig(**config)
        except FileNotFoundError as exc:
            logger.error("File %s not found", config_file_name)
            raise FileNotFoundError("File not found") from exc
