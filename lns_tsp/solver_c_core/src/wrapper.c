/**
 * @file main.c
 * @author Armin Sadeghi (a6sadegh@uwaterloo.ca)
 * @brief
 * @version 0.1
 * @date 2023-09-17
 */

#include <Python.h>
#include <math.h>
#include <stdio.h>

#include "data_loader/load_instance.h"
#include "insertions/cheapest_insertion.h"
#include "insertions/nearest_insertion.h"
#include "removals/cluster_removal.h"
#include "removals/random_removal.h"
#include "removals/worst_removal.h"
#include "twist_move.h"
#include "util/objective.h"

static PyMethodDef solver_c_methods[] = {
    {"load_instance", read_instance_from_file_py, METH_VARARGS,
     "Load a TSP instance from a file"},
    {"objective_value", objective_value, METH_VARARGS,
     "Calculate the objective value of a tour"},
    {"random_removal", random_removal, METH_VARARGS,
     "Randomly remove a set of nodes from the tour"},
    {"worst_removal", worst_removal, METH_VARARGS,
     "Remove the nodes with the worst insertion cost"},
    {"cluster_removal", cluster_removal, METH_VARARGS,
     "Remove a cluster of nodes"},
    {"nearest_insertion", nearest_insertion, METH_VARARGS,
     "Insert nodes based on their distance to the tour"},
    {"cheapest_insertion", cheapest_insertion, METH_VARARGS,
     "Insert nodes based on their insertion cost"},
    {"twist_move", twist_move, METH_VARARGS,
     "Twist the tour to improve the objective value"},
    {NULL, NULL, 0, NULL} // Sentinel
};

static struct PyModuleDef solver_core_module = {
    PyModuleDef_HEAD_INIT,
    "solver_c",                            // m_name
    "C implementation of LNS heuristics for TSP", // m_doc
    -1,                                    // m_size
    solver_c_methods,                     // m_methods
    NULL,                                  // m_slots
    NULL,                                  // m_traverse
    NULL,                                  // m_clear
    NULL                                   // m_free
};

PyMODINIT_FUNC PyInit_solver_core(void) {
  PyObject *m = PyModule_Create(&solver_core_module);
  if (m == NULL)
    return NULL;
  if (PyType_Ready(&PyTSPInstance_Type) < 0) {
    return NULL;
  }
  Py_INCREF(&PyTSPInstance_Type);
  PyModule_AddObject(m, "TSPInstance", (PyObject *)&PyTSPInstance_Type);
  return m;
}