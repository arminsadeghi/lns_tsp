"""Data loader class for reading the TSP data from the file."""

# pylint: disable=import-error
from typing import List

from lns_tsp.setup_logger import get_logger

logger = get_logger(__name__)


class DataLoader:
    """Data loader class for reading the TSP data from the file"""

    def __init__(self):
        pass

    @staticmethod
    def _read_optimal_tour(data: list):
        """reads the instance optimal tour

        Args:
            data (list): data in the file
            instance (TSPInstance): tsp instance object
        """
        logger.info("Reading optimal tour")
        optimal_tour = []
        optimal_objective_value = None
        for idx, line in enumerate(data):
            if line.strip() == "TOUR_SECTION":
                while data[idx + 1].strip() != "-1":
                    optimal_tour.append(int(data[idx + 1].strip()) - 1)
                    idx += 1
            if line.strip() == "COMMENT":
                optimal_objective_value = float(
                    data[idx + 1].strip().split(":")[1].strip()
                )
                break
        logger.info("OPTIMAL TOUR:" + str(optimal_tour))
        return optimal_tour

    @staticmethod
    def read_edge_weight_section(data: list, instance):
        """reads the edge weight section of the instance"""
        data = " ".join(data).split()
        instance.init_dist_matrix()
        try:
            match instance.edge_weight_format:
                case "FULL_MATRIX":
                    for i in range(instance.dimension):
                        instance.distance_matrix.append(
                            [
                                float(x)
                                for x in data[
                                    i
                                    * instance.dimension : (i + 1)
                                    * instance.dimension
                                ]
                            ]
                        )
                case "UPPER_ROW":
                    idx = 0
                    for i in range(instance.dimension - 1):
                        for j in range(i + 1, instance.dimension):
                            dist = float(data[idx])
                            instance.distance_matrix[i][j] = dist
                            instance.distance_matrix[j][i] = dist
                            idx += 1
                case "UPPER_DIAG_ROW":
                    idx = 0
                    for i in range(instance.dimension - 1):
                        for j in range(i + 1, instance.dimension):
                            dist = float(data[idx])
                            instance.distance_matrix[i][j] = dist
                            instance.distance_matrix[j][i] = dist
                            idx += 1
                case "LOWER_DIAG_ROW":
                    idx = 0
                    for i in range(instance.dimension):
                        for j in range(i + 1):
                            instance.distance_matrix[i][j] = float(data[idx])
                            instance.distance_matrix[j][i] = float(data[idx])
                            idx += 1
                case _:
                    raise ValueError(
                        f"Edge weight format {instance.edge_weight_format} not supported"
                    )
        except Exception as exc:
            logger.error("Error in reading the edge weight section")
            raise ValueError("Error in reading the edge weight section") from exc
        return instance

    @staticmethod
    def read_optimal_tour(filename: str):
        """reads the optimal tour from the file"""
        try:
            with open(filename, "r", encoding="utf-8") as file:
                return DataLoader._read_optimal_tour(file.readlines())
        except FileNotFoundError:
            logger.warning("Optimal tour file %s not found", filename)

    @staticmethod
    def write_to_file(filename, instance, write_distance_matrix=True):
        """Write the instance to the file."""
        with open(filename, "w", encoding="utf-8") as file:
            to_file = "NODE_COORD_SECTION\n"
            for node in instance.nodes:
                to_file += f"{node.location.x}, {node.location.y}\n"
            file.write(to_file)

            if write_distance_matrix:
                to_file = "EDGE_WEIGHT_SECTION\n"
                for row in instance.distance_matrix:
                    to_file += ",".join([str(x) for x in row]) + "\n"
                file.write(to_file)

    @staticmethod
    def write_solution_to_file(filename, tour: List):
        "write the solution to the file."
        with open(filename, "w", encoding="utf-8") as file:
            file.write("TOUR_SECTION\n")
            file.write("\n".join([str(x) for x in tour]))
            file.write("\n-1\n")
            file.write("EOF\n")
