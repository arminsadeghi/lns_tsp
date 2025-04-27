/**
 * @file twist_move.h
 * @author Armin Sadeghi (a6sadegh@uwaterloo.ca)
 * @brief Twist the tour by swapping two edges.
 * @version 0.1
 * @date 2023-10-15
 */

#ifndef TOOLAS_TSP_SOLVER_INCLUDE_TWIST_MOVE_H_
#define TOOLAS_TSP_SOLVER_INCLUDE_TWIST_MOVE_H_

#include <Python.h>

#include "tsp_instance.h"
#include "util/node_dlist.h"
/**
 * @brief Twist the tour by swapping two edges.
 * @param tour The tour to be twisted.
 * @param nodes_to_add The nodes to be added to the tour.
 */
void twist_move_c(TSPInstance *instance, NodeList *tour);
void twist_(NodeList *node1, NodeList *node2);
void revert_twist_(NodeList *node1, NodeList *node2);
extern PyObject *twist_move(PyObject *self, PyObject *args);
#endif // TOOLAS_TSP_SOLVER_INCLUDE_TWIST_MOVE_H_
