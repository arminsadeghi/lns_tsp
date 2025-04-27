/**
 * @file worst_removal.h
 * @author Armin Sadeghi (a6sadegh@uwaterloo.ca)
 * @brief
 * @version 0.1
 * @date 2023-09-17
 */

#ifndef SOLVER_SRC_REMOVALS_WORST_REMOVAL_H_
#define SOLVER_SRC_REMOVALS_WORST_REMOVAL_H_

#include "tsp_instance.h"
#include <Python.h>

/**
 * @brief remove the nodes with the worst insertion costs
 */
void worst_removal_c(TSPInstance *instance, int *tour, int tour_length,
                     int num_to_delete);

extern PyObject *worst_removal(PyObject *self, PyObject *args);

#endif // SOLVER_SRC_REMOVALS_WORST_REMOVAL_H_