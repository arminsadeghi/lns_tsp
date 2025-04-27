/**
 * @file node_dlist.h
 * @author Armin Sadeghi (a6sadegh@uwaterloo.ca)
 * @brief Doubly linked list of nodes
 * @version 0.1
 * @date 2023-10-14
 * @copyright Copyright (c) 2023
 */

#ifndef SOLVER_INCLUDE_UTIL_NODE_DLIST_H_
#define SOLVER_INCLUDE_UTIL_NODE_DLIST_H_

#include <Python.h>

typedef struct NodeList {
  int node;
  struct NodeList *next;
  struct NodeList *prev;
} NodeList;
/**
 * @brief Create a double linked list of nodes from the given tour.
 *
 * @param tour list of nodes
 * @param tour_length length of the tour
 * @param loop true if the double linked list should be a loop
 * @return NodeList*
 */
NodeList *create_node_list(int *tour, int tour_length, int loop);
/**
 * @brief Create a double linked list of nodes from the given tour.
 *
 * @param tour list of nodes directly from Python
 * @param tour_length length of the tour
 * @param loop true if the double linked list should be a loop
 * @return NodeList*
 */
NodeList *create_node_list_from_python_list(PyObject *tour, int tour_length,
                                            int loop);
NodeList *remove_and_free_node_c(NodeList *node);
void free_node_list(NodeList *list);
#endif // SOLVER_INCLUDE_UTIL_NODE_DLIST_H_