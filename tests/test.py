from lns_tsp.solver_core import load_instance

instance = load_instance("data/att48.tsp")
print(instance.instance_name)
