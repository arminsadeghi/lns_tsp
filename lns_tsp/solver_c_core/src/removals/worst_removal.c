/**
 * @file worst_removal.c
 * @author Armin Sadeghi (a6sadegh@uwaterloo.ca)
 * @brief
 * @version 0.1
 * @date 2023-09-17
 */

#include <Python.h>

#include "heuristic_util/removal_util.h"
#include "removals/worst_removal.h"

void worst_removal_c(TSPInstance *instance, int *tour, int tour_length,
                     int num_to_delete) {
  //  remove nodes with worst insertion cost
  int num_deleted = 0;
  while (num_deleted < num_to_delete) {
    double worst_cost = 0;
    int worst_city = -1;
    for (int i = 1; i < tour_length; ++i) {
      if (tour[i] == -1)
        continue; // skip removed nodes

      double cost = removal_cost_c(instance, tour, tour_length, i);
      if (cost > worst_cost) {
        worst_cost = cost;
        worst_city = i;
      }
    }
    if (worst_city == -1)
      break; // no more nodes to delete

    tour[worst_city] = -1;
    num_deleted++;
  }
}

extern PyObject *worst_removal(PyObject *self, PyObject *args) {
  PyObject *py_tour;
  PyObject *py_instance;
  int py_tour_length;
  int py_num_to_delete;

  if (!PyArg_ParseTuple(args, "OOii", &py_instance, &py_tour, &py_tour_length,
                        &py_num_to_delete)) {
    return NULL;
  }

  int *tour = (int *)malloc(py_tour_length * sizeof(int));
  for (int i = 0; i < py_tour_length; ++i) {
    PyObject *py_item = PyList_GetItem(py_tour, i);
    tour[i] = PyLong_AsLong(py_item);
  }

  PyTSPInstance *py_instance_cast = (PyTSPInstance *)py_instance;

  worst_removal_c(py_instance_cast->instance, tour, py_tour_length,
                  py_num_to_delete);

  PyObject *py_new_tour = PyList_New(py_tour_length);
  for (int i = 0; i < py_tour_length; ++i) {
    PyList_SetItem(py_new_tour, i, PyLong_FromLong(tour[i]));
  }
  free(tour);
  return py_new_tour;
}