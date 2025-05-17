/**
 * @file random_removal.c
 * @author Armin Sadeghi (a6sadegh@uwaterloo.ca)
 * @brief
 * @version 0.1
 * @date 2023-09-17
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "removals/random_removal.h"
#include "tsp_instance.h"

/**
 * @brief randomly delete a set of nodes from the tour
 * @param tour the current tour
 * @param tour_length the number of cities in the tour
 * @param num_to_delete  number of cities to delete
 */
void random_removal_c(int *tour, int tour_length, int num_to_delete) {
  if (num_to_delete >= tour_length) {
    num_to_delete = tour_length - 1;
  }
  srand(time(NULL)); // Initialize random number generator.

  while (num_to_delete > 0) {
    int city = rand() % tour_length;
    if (tour[city] != -1) {
      tour[city] = -1;
      num_to_delete--;
    }
  }
}

extern PyObject *random_removal(PyObject *_self, PyObject *args) {
  (void)_self; // Unused parameter
  PyObject *py_tour;
  int py_tour_length;
  int py_num_to_delete;

  if (!PyArg_ParseTuple(args, "Oii", &py_tour, &py_tour_length,
                        &py_num_to_delete)) {
    return NULL;
  }

  int *tour = (int *)malloc(py_tour_length * sizeof(int));
  for (int i = 0; i < py_tour_length; ++i) {
    PyObject *py_item = PyList_GetItem(py_tour, i);
    tour[i] = PyLong_AsLong(py_item);
  }
  random_removal_c(tour, py_tour_length, py_num_to_delete);

  PyObject *py_new_tour = PyList_New(py_tour_length);
  for (int i = 0; i < py_tour_length; ++i) {
    PyList_SetItem(py_new_tour, i, PyLong_FromLong(tour[i]));
  }
  free(tour);
  return py_new_tour;
}