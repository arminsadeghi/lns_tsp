
/**Nearest insertion.*/

#ifndef SOLVER_SRC_INSERTIONS_NEAREST_INSERTION_H_
#define SOLVER_SRC_INSERTIONS_NEAREST_INSERTION_H_

#include "tsp_instance.h"
#include "util/node_dlist.h"
#include <Python.h>

/**
 * @brief Insert the node closest to the current ones.
 */
void nearest_insertion_c(TSPInstance *instance, NodeList *tour,
                         NodeList *nodes_to_add);

extern PyObject *nearest_insertion(PyObject *self, PyObject *args);

#endif // SOLVER_SRC_INSERTIONS_NEAREST_INSERTION_H_