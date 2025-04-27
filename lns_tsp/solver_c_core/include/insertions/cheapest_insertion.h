/** Cheapest insertion.*/

#ifndef SOLVER_SRC_INSERTIONS_CHEAPEST_INSERTION_H_
#define SOLVER_SRC_INSERTIONS_CHEAPEST_INSERTION_H_

#include <Python.h>

#include "tsp_instance.h"
#include "util/node_dlist.h"
/**
 * @brief remove the nodes with the worst insertion costs
 */
void cheapest_insertion_c(TSPInstance *instance, NodeList *tour,
                          NodeList *nodes_to_add);

extern PyObject *cheapest_insertion(PyObject *self, PyObject *args);

#endif // SOLVER_SRC_INSERTIONS_CHEAPEST_INSERTION_H_