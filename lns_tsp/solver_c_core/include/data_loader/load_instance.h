/**
 * @file load_instance.h
 * @author Armin Sadeghi (sadeghiy.armin[at]gmail.com)
 * @version 0.1
 */

#ifndef LOAD_INSTANCE_H_
#define LOAD_INSTANCE_H_
#include "data_loader/distance_matrix.h"
#include "tsp_instance.h"
#include <stdio.h>
#include <stdlib.h>

void print_instance(const TSPInstance *instance);
FILE *open_file(const char *filename);
void read_file(FILE *file, TSPInstance *instance);
void read_node_section(FILE *file, TSPInstance *instance);
int read_instance_from_file(TSPInstance *instance, char *filename);
PyObject *read_instance_from_file_py(PyObject *self, PyObject *args);
#endif // LOAD_INSTANCE_H_
