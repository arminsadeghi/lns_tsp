"""plot tsp instance."""

import matplotlib.pyplot as plt

colors = ["blue", "green", "yellow", "orange", "purple", "pink"]


def plot_tsp_instance(instance, tours):
    """Plots the TSP instance."""
    x_locations = [instance.nodes[i].location.x for i in range(instance.dimension)]
    y_locations = [instance.nodes[i].location.y for i in range(instance.dimension)]
    plt.scatter(x_locations, y_locations, c="red")

    for idx, tour in enumerate(tours):
        if not tour:
            continue
        for current_node, next_node in zip(tour, tour[1:]):
            plt.plot(
                [
                    instance.nodes[current_node].location.x,
                    instance.nodes[next_node].location.x,
                ],
                [
                    instance.nodes[current_node].location.y,
                    instance.nodes[next_node].location.y,
                ],
                c=colors[idx],
            )
        plt.plot(
            [
                instance.nodes[tour[-1]].location.x,
                instance.nodes[tour[0]].location.x,
            ],
            [
                instance.nodes[tour[-1]].location.y,
                instance.nodes[tour[0]].location.y,
            ],
            c=colors[idx],
        )
    plt.show()
