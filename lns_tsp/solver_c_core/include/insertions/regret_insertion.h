/**
 * @file regret_insertion.h
 * @author Armin Sadeghi (sadeghiy.armin[at]gmail.com)
 * @version 0.1
 */

#ifndef SOLVER_SRC_INSERTIONS_REGRET_INSERTION_H_
#define SOLVER_SRC_INSERTIONS_REGRET_INSERTION_H_

#include "heuristic_util/insertion_util.h"
#include "tsp_instance.h"
#include "util/node_dlist.h"
#include <Python.h>

/**
 * @brief Insert nodes based on the regret.
 */
void regret_insertion_c(TSPInstance *instance, NodeList *tour,
                        NodeList *nodes_to_add, int k);

void find_k_best_insertions_c(TSPInstance *instance, NodeList *tour,
                              NodeList *node, Insertion *insertions, int k);

extern PyObject *regret_insertion(PyObject *self, PyObject *args);

#endif // SOLVER_SRC_INSERTIONS_REGRET_INSERTION_H_