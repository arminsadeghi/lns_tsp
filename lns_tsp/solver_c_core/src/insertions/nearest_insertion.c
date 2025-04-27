
/** Nearest insertion heuristic.*/

#include <float.h>
#include <stdio.h>
#include <stdlib.h>

#include <Python.h>

#include "heuristic_util/insertion_util.h"
#include "insertions/nearest_insertion.h"
#include "util/node_dlist.h"

void nearest_insertion_c(TSPInstance *instance, NodeList *tour,
                         NodeList *nodes_to_add) {
  // Inserts nodes based on their insertion cost.
  while (true) {
    NodeList *nearest_node = NULL;
    NodeList *current_nodes_to_add = nodes_to_add;
    double closest_distance = DBL_MAX;
    while (true) {
      NodeList *current_tour_node = tour;
      while (true) {
        double distance = instance->distance_matrix[current_tour_node->node]
                                                   [current_nodes_to_add->node];
        if (distance < closest_distance) {
          closest_distance = distance;
          nearest_node = current_nodes_to_add;
        }
        current_tour_node = current_tour_node->next;
        if (current_tour_node == tour)
          break;
      }
      current_nodes_to_add = current_nodes_to_add->next;
      if (current_nodes_to_add == nodes_to_add)
        break;
    }
    if (nearest_node == NULL)
      break;
    Insertion best_insertion = best_insertion_c(instance, tour, nearest_node);
    if (best_insertion.pos == NULL) {
      break; // no more nodes to add
    }
    insert_node_c(best_insertion.pos, nearest_node);
    nodes_to_add = remove_and_free_node_c(nearest_node);
    if (nodes_to_add == NULL)
      break;
    // insert the last node to the tour.
    if (nodes_to_add->next == NULL) {
      Insertion best_insertion = best_insertion_c(instance, tour, nodes_to_add);
      insert_node_c(best_insertion.pos, nodes_to_add);
      free(nodes_to_add);
      break;
    }
  }
}

extern PyObject *nearest_insertion(PyObject *self, PyObject *args) {
  PyObject *py_tour;
  PyObject *py_instance;
  int py_tour_length;
  PyObject *py_nodes_to_add;
  int py_num_to_add;

  if (!PyArg_ParseTuple(args, "OOiOi", &py_instance, &py_tour, &py_tour_length,
                        &py_nodes_to_add, &py_num_to_add)) {
    return NULL;
  }
  NodeList *tour =
      create_node_list_from_python_list(py_tour, py_tour_length, 1);
  NodeList *nodes_to_add =
      create_node_list_from_python_list(py_nodes_to_add, py_num_to_add, 1);

  PyTSPInstance *py_instance_cast = (PyTSPInstance *)py_instance;
  nearest_insertion_c(py_instance_cast->instance, tour, nodes_to_add);

  PyObject *py_new_tour = PyList_New(py_tour_length + py_num_to_add);
  if (!py_new_tour) {
    PyErr_SetString(PyExc_MemoryError,
                    "Failed to allocate memory for new list.");
    return NULL;
  }
  NodeList *current = tour;
  int index = 0;
  while (true) {
    PyList_SetItem(py_new_tour, index, PyLong_FromLong(current->node));
    current = current->next;
    index++;
    if (current == tour)
      break;
  }
  NodeList *current_node = nodes_to_add;
  free_node_list(tour);
  return py_new_tour;
}