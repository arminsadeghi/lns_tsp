"""The main entry point for the TSP solver."""

import argparse

from lns_tsp.data_util import DataLoader
from lns_tsp.plotting.plot_tsp_instance import plot_tsp_instance
from lns_tsp.setup_logger import get_logger
from lns_tsp.solver import Solver
from lns_tsp.solver_config import SolverConfig

logger = get_logger("lns_tsp_solver")


def main():
    """Main entry point for the TSP solver."""
    parser = argparse.ArgumentParser(description="TSP solver")
    parser.add_argument(
        "-i",
        "--instance",
        type=str,
        required=True,
        help="Path to the instance file.",
    )
    parser.add_argument(
        "-c",
        "--config_file",
        type=str,
        required=False,
        default=None,
        help="Path to the solver config file.",
    )
    args = parser.parse_args()

    config = (
        SolverConfig.from_config_file(args.config_file)
        if args.config_file is not None
        else SolverConfig()
    )

    solver = Solver(config, args.instance)
    solver.run()


if __name__ == "__main__":
    main()
