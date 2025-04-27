/**
 * @file objective.h
 * @author Armin Sadeghi (a6sadegh@uwaterloo.ca)
 * @brief
 * @version 0.1
 * @date 2023-09-17
 */

#ifndef SOLVER_INCLUDE_UTIL_OBJECTIVE_H_
#define SOLVER_INCLUDE_UTIL_OBJECTIVE_H_

#include <Python.h>

#include "tsp_instance.h"
#include "util/node_dlist.h"

/**
 * @brief calculate the objective value of a tour
 * @param tour
 * @param n
 * @return double
 */
double objective_value_c(TSPInstance *instance, int *tour, int n);

/**
 * @brief calculate the objective value of a tour
 * @param tour
 * @return double
 */
double objective_value_node_list(TSPInstance *instance, NodeList *tour);
/**
 * @brief calculate the objective value of a tour
 * @param self
 * @param args
 * @return PyObject*
 */
extern PyObject *objective_value(PyObject *self, PyObject *args);

#endif // SOLVER_INCLUDE_UTIL_OBJECTIVE_H_