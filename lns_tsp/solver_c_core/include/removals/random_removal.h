/**
 * @file random_removal.h
 * @author Armin Sadeghi (a6sadegh@uwaterloo.ca)
 * @brief
 * @version 0.1
 * @date 2023-09-17
 *
 */

#ifndef SOLVER_SRC_REMOVALS_RANDOM_REMOVAL_H_
#define SOLVER_SRC_REMOVALS_RANDOM_REMOVAL_H_

#include <Python.h>
#include <stdlib.h>
#include <time.h>

void random_removal_c(int* tour, int tour_length, int num_to_delete);
extern PyObject* random_removal(PyObject* self, PyObject* args);
#endif  // SOLVER_SRC_REMOVALS_RANDOM_REMOVAL_H_