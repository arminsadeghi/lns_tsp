/**
 * @file cluster_removal.c
 * @author Armin Sadeghi (a6sadegh@uwaterloo.ca)
 * @brief
 * @version 0.1
 * @date 2023-09-17
 */

#include <Python.h>

#include "heuristic_util/removal_util.h"
#include "removals/cluster_removal.h"

void cluster_removal_c(TSPInstance *instance, int *tour, int tour_length,
                       int num_to_delete) {
  // Define the cluster size and number of nodes deleted
  int cluster_size = num_to_delete;
  // Pick a random starting point
  int start = rand() % tour_length;

  // Calculate distances between nodes and the starting point and store them in
  // an array of pairs
  typedef struct {
    double distance;
    int node;
  } NodeDist;

  NodeDist distances[tour_length];
  for (int i = 0; i < tour_length; ++i) {
    distances[i].distance = instance->distance_matrix[tour[i]][tour[start]];
    distances[i].node = tour[i];
  }

  // Sort nodes by distance to the starting point
  for (int i = 0; i < tour_length - 1; ++i) {
    for (int j = i + 1; j < tour_length; ++j) {
      if (distances[i].distance > distances[j].distance) {
        NodeDist temp = distances[i];
        distances[i] = distances[j];
        distances[j] = temp;
      }
    }
  }

  // Remove nodes in tour that are in the cluster
  for (int i = 0; i < cluster_size; ++i) {
    tour[distances[i].node] = -1;
  }
}

extern PyObject *cluster_removal(PyObject *self, PyObject *args) {
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
  cluster_removal_c(py_instance_cast->instance, tour, py_tour_length,
                    py_num_to_delete);

  PyObject *py_new_tour = PyList_New(py_tour_length);
  for (int i = 0; i < py_tour_length; ++i) {
    PyList_SetItem(py_new_tour, i, PyLong_FromLong(tour[i]));
  }

  free(tour);

  return py_new_tour;
}