/**
 * @file regret_insertion.c
 * @author Armin Sadeghi (sadeghiy.armin[at]gmail.com)
 * @version 0.1
 */

#include "insertions/regret_insertion.h"
#include "heuristic_util/insertion_util.h"
#include <float.h>
#include <stdlib.h>

void regret_insertion_c(TSPInstance *instance, NodeList *tour,
                        NodeList *nodes_to_add, int k) {
  if (k < 1) {
    fprintf(stderr, "k must be at least 1\n");
    return;
  }
  if (k >= instance->dimension) {
    fprintf(stderr, "k must be less than the number of nodes\n");
    return;
  }
  while (true) {
    NodeList *current_node = nodes_to_add;
    NodeList *best_node = NULL;
    Insertion best_insertion;
    double best_regret = -1.0;

    while (true) {
      Insertion insertions[k];
      find_k_best_insertions_c(instance, tour, current_node, insertions, k);

      break;
      // Compute regret: sum of (cost_i - cost_1) for i = 2..K
      double regret = 0.0;
      for (int i = 1; i < k; i++) {
        regret += insertions[i].cost - insertions[0].cost;
      }

      // Pick node with highest regret
      if (regret > best_regret) {
        best_regret = regret;
        best_node = current_node;
        best_insertion = insertions[0]; // use the best of k options
      }

      current_node = current_node->next;
      if (current_node == nodes_to_add)
        break;
    }

    if (best_node == NULL || best_insertion.pos == NULL)
      break;

    insert_node_c(best_insertion.pos, best_node);
    nodes_to_add = remove_and_free_node_c(best_node);
    if (nodes_to_add == NULL)
      break;

    break;
  }
  NodeList *current_node = nodes_to_add;
  while (true) {
    insert_node_c(tour, current_node);
    current_node = current_node->next;
    if (current_node == nodes_to_add)
      break;
    printf("current_node: %d\n", current_node->node);
  }
}

void find_k_best_insertions_c(TSPInstance *instance, NodeList *tour,
                              NodeList *node, Insertion *insertions, int k) {
  // Fill with worst-case defaults
  for (int i = 0; i < k; i++) {
    insertions[i].cost = DBL_MAX;
    insertions[i].pos = NULL;
  }

  for (NodeList *pos = tour; pos != NULL; pos = pos->next) {
    double cost = insertion_cost_c(instance, pos, node);
    Insertion ins = {cost, pos};
    // Insert into the sorted array
    for (int i = 0; i < k; i++) {
      printf("insertions[%d].cost: %f\n", i, insertions[i].cost);
      if (insertions[i].cost > ins.cost) {
        // Shift elements to the right
        for (int j = k - 1; j > i; j--) {
          insertions[j] = insertions[j - 1];
        }
        insertions[i] = ins;
        break;
      }
    }
  }
}

extern PyObject *regret_insertion(PyObject *_self, PyObject *args) {
  (void)_self; // Unused parameter
  PyObject *py_tour;
  PyObject *py_instance;
  int py_tour_length;
  PyObject *py_nodes_to_add;
  int py_num_to_add;
  int k;

  if (!PyArg_ParseTuple(args, "OOiOii", &py_instance, &py_tour, &py_tour_length,
                        &py_nodes_to_add, &py_num_to_add, &k)) {
    return NULL;
  }
  NodeList *tour =
      create_node_list_from_python_list(py_tour, py_tour_length, 1);
  NodeList *nodes_to_add =
      create_node_list_from_python_list(py_nodes_to_add, py_num_to_add, 1);

  PyTSPInstance *py_instance_cast = (PyTSPInstance *)py_instance;
  regret_insertion_c(py_instance_cast->instance, tour, nodes_to_add, k);

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
  free_node_list(tour);
  return py_new_tour;
}