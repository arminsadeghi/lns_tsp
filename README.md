# LNS solver in C with python bindings

This is an implementation of the ALNS solver for the TSP problem. The core algorithm is written in C, and the Python bindings. The goal is to provide an easy-to-use and fast TSP solver that can be used in Python projects.

## Installation

To install the package, you can use pip:

```bash
./scripts/install.sh
```

## Usage

To use the package, you can import it in your Python code:

```python
from lns_tsp.solver import Solver
from lns_tsp.solver_config import SolverConfig

# Create a solver config
config = SolverConfig.read_from_file("path/to/your/config.json")
# Create a solver
solver = Solver(config, "path/to/your/tsp/file.tsp")
solver.run()
```

## Configuration

The solver can be configured using a JSON file. The configuration file should contain the following fields:

- `max_time`: The maximum time in seconds to run the solver.
- `max_iterations`: The maximum number of iterations to run the solver.
- `max_no_improvement`: The maximum number of iterations without improvement to run the solver.
- `max_num_to_remove`: The maximum number of nodes to remove from the solution.
- `log_frequency`: The frequency of logging the solution.
- `log`: The boolean to enable logging.
- `post_processing_probability`: The probability of applying post-processing after each iteration.
- `simulated_annealing`:
  - `initial_temperature`: The initial temperature for the simulated annealing.
  - `cooling_rate`: The cooling rate for the simulated annealing.
- `heuristic`:
  - `heuristic_type`: The type of heuristic to use for removal and insertion.
  - `heuristic_probability`: The probability of applying the heuristic.
  - `increment`: The increment for the heuristic probability.

The default configuration file is provided in the `lns_tps/config/default_solver_config.json`. You can modify it to suit your needs.