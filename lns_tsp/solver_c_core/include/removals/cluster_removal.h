/**
 * @file cluster_removal.h
 * @author Armin Sadeghi (a6sadegh@uwaterloo.ca)
 * @brief
 * @version 0.1
 * @date 2023-09-17
 *
 */

#ifndef SOLVER_SRC_REMOVALS_CLUSTER_REMOVAL_H_
#define SOLVER_SRC_REMOVALS_CLUSTER_REMOVAL_H_

#include "tsp_instance.h"
#include <Python.h>
#include <stdlib.h>
#include <time.h>

void cluster_removal_c(TSPInstance *instance, int *tour, int tour_length,
                       int num_to_delete);
extern PyObject *cluster_removal(PyObject *self, PyObject *args);
#endif // SOLVER_SRC_REMOVALS_CLUSTER_REMOVAL_H_