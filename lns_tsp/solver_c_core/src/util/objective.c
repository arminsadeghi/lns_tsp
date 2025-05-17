/**
 * @file objective.c
 * @author Armin Sadeghi (a6sadegh@uwaterloo.ca)
 * @brief
 * @version 0.1
 * @date 2023-09-17
 */

#include "util/objective.h"
#include <stdbool.h>
#include <stdlib.h>

double objective_value_c(TSPInstance *instance, int *tour, int tour_length) {
  double objective_value = 0;
  for (int i = 0; i < tour_length - 1; ++i) {
    if (tour[i] == -1 || tour[i + 1] == -1) {
      continue;
    }
    objective_value += instance->distance_matrix[tour[i]][tour[i + 1]];
  }
  if (tour[tour_length - 1] != -1 && tour[0] != -1) {
    objective_value +=
        instance->distance_matrix[tour[tour_length - 1]][tour[0]];
  }
  return objective_value;
}

double objective_value_node_list(TSPInstance *instance, NodeList *tour) {
  double objective_value = 0;
  NodeList *current_node = tour;
  while (true) {
    objective_value +=
        instance->distance_matrix[current_node->node][current_node->next->node];
    current_node = current_node->next;
    if (current_node == tour)
      break;
  }
  return objective_value;
}

extern PyObject *objective_value(PyObject *_self, PyObject *args) {
  (void)_self; // Unused parameter
  PyObject *py_tour;
  PyObject *py_instance;
  int tour_length;

  if (!PyArg_ParseTuple(args, "OOi", &py_instance, &py_tour, &tour_length)) {
    return NULL;
  }

  int *tour = (int *)malloc(tour_length * sizeof(int));
  for (int i = 0; i < tour_length; ++i) {
    PyObject *py_item = PyList_GetItem(py_tour, i);
    tour[i] = PyLong_AsLong(py_item);
  }
  PyTSPInstance *py_instance_cast = (PyTSPInstance *)py_instance;
  float objective_value =
      objective_value_c(py_instance_cast->instance, tour, tour_length);
  free(tour);
  return Py_BuildValue("d", objective_value);
}
