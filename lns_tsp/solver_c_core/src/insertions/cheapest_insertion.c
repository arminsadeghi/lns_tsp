/** Cheapest insertion heuristic.*/

#include <float.h>
#include <stdio.h>
#include <stdlib.h>

#include <Python.h>

#include "heuristic_util/insertion_util.h"
#include "insertions/cheapest_insertion.h"
#include "util/node_dlist.h"

void cheapest_insertion_c(TSPInstance *instance, NodeList *tour,
                          NodeList *nodes_to_add) {
  // Inserts nodes based on their insertion cost.
  while (true) {
    NodeList *current_node_to_add = nodes_to_add;
    Insertion best_insertion;
    best_insertion.cost = DBL_MAX;
    NodeList *node_to_insert = NULL;
    while (true) {
      Insertion insertion =
          best_insertion_c(instance, tour, current_node_to_add);

      if (insertion.cost < best_insertion.cost) {
        best_insertion.cost = insertion.cost;
        best_insertion.pos = insertion.pos;
        node_to_insert = current_node_to_add;
      }
      current_node_to_add = current_node_to_add->next;
      if (current_node_to_add == nodes_to_add)
        break;
    }
    if (best_insertion.pos == NULL) {
      break; // no more nodes to add
    }
    insert_node_c(best_insertion.pos, node_to_insert);
    nodes_to_add = remove_and_free_node_c(node_to_insert);
    if (nodes_to_add == NULL)
      break;
    // insert the last node to the tour.
    if (nodes_to_add->next == NULL) {
      Insertion best_insertion = best_insertion_c(instance, tour, nodes_to_add);
      insert_node_c(best_insertion.pos, nodes_to_add);
      free(nodes_to_add);
      return;
    }
  }
}

extern PyObject *cheapest_insertion(PyObject *self, PyObject *args) {
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
  cheapest_insertion_c(py_instance_cast->instance, tour, nodes_to_add);

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