/**
 * @file twist_move.c
 * @author Armin Sadeghi (a6sadegh@uwaterloo.ca)
 * @version 0.1
 * @date 2023-10-15
 * @copyright Copyright (c) 2023
 */

#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#include "twist_move.h"
#include "util/node_dlist.h"
#include "util/objective.h"
#include "util/tour_util.h"

void twist_move_c(TSPInstance *instance, NodeList *tour) {
  double starting_objective_value = objective_value_node_list(instance, tour);
  double best_objective_value = starting_objective_value;
  // copy the tour into a new temporary tour.
  NodeList *temp_tour = malloc(sizeof(NodeList));
  temp_tour->node = tour->node;
  temp_tour->next = NULL;
  temp_tour->prev = NULL;
  NodeList *current = tour->next;
  NodeList *temp_current = temp_tour;
  while (true) {
    if (current == tour) {
      break;
    }
    NodeList *new_node = malloc(sizeof(NodeList));
    new_node->node = current->node;
    new_node->next = NULL;
    new_node->prev = temp_current;
    temp_current->next = new_node;
    temp_current = temp_current->next;
    current = current->next;
  }
  temp_current->next = temp_tour;
  temp_tour->prev = temp_current;

  NodeList *temp_tour_start = temp_tour;
  NodeList *current_node = temp_tour;
  NodeList *next_node = current_node->next;
  while (true) {
    while (true) {
      twist_(current_node, next_node);
      double current_objective_value =
          objective_value_node_list(instance, temp_tour);
      if (current_objective_value < best_objective_value) {
        best_objective_value = current_objective_value;
        next_node = current_node->next;
      } else {
        twist_(next_node, current_node);
        next_node = next_node->next;
      }
      if (next_node->next == current_node)
        break;
    }
    current_node = current_node->next;
    next_node = current_node->next;
    if (current_node == temp_tour_start)
      break;
  }

  // copy the temporary tour back into the original tour.
  current_node = tour;
  next_node = temp_tour;
  while (true) {
    current_node->node = next_node->node;
    current_node = current_node->next;
    next_node = next_node->next;
    if (next_node == temp_tour)
      break;
  }
  free_node_list(temp_tour);
}

void twist_(NodeList *node1, NodeList *node2) {
  NodeList *node1_prev = node1->prev;
  NodeList *node2_next = node2->next;

  node1_prev->next = node2;
  node1->next = node2_next;
  node2_next->prev = node1;
  // reverse the direction of the nodes between node1 and node2.
  NodeList *current_node = node2;
  while (true) {
    NodeList *temp = current_node->next;
    current_node->next = current_node->prev;
    current_node->prev = temp;
    if (current_node->next == node1) {
      node1->prev = current_node;
    }
    current_node = current_node->next;
    if (current_node == node1)
      break;
  }
  node2->prev = node1_prev;
}

void revert_twist_(NodeList *node1, NodeList *node2) {
  NodeList *node2_next = node1->next;

  node2->next = node1;
  node1->next = node2_next;
  node2_next->prev = node1;

  // reverse the direction of the nodes between node1 and node2.
  NodeList *current_node = node1;
  while (true) {
    NodeList *temp = current_node->next;
    current_node->next = current_node->prev;
    current_node->prev = temp;
    current_node = current_node->next;
    if (current_node == node1)
      break;
  }
}

extern PyObject *twist_move(PyObject *_self, PyObject *args) {
  (void)_self; // Unused parameter
  PyObject *py_tour;
  PyObject *py_instance;
  int py_tour_length;

  if (!PyArg_ParseTuple(args, "OOi", &py_instance, &py_tour, &py_tour_length)) {
    return NULL;
  }
  NodeList *tour =
      create_node_list_from_python_list(py_tour, py_tour_length, 1);
  PyTSPInstance *py_instance_cast = (PyTSPInstance *)py_instance;
  twist_move_c(py_instance_cast->instance, tour);

  PyObject *py_new_tour = PyList_New(py_tour_length);
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