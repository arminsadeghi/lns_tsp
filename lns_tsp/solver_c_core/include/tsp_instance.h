/**
 * @file tsp_instance.h
 * @author Armin Sadeghi (sadeghiy.armin[at]gmail.com)
 * @version 0.1
 */

#ifndef TSP_INSTANCE_H_
#define TSP_INSTANCE_H_
#include <Python.h>
#include <stdlib.h>

typedef struct {
  float x;
  float y;
  int id;
} Node;

typedef struct {
  char instance_name[100];
  int dimension;
  float **distance_matrix;
  Node *nodes;
  char type[100];
  char edge_weight_type[100];
  char edge_weight_format[100];
} TSPInstance;
extern PyTypeObject PyTSPInstance_Type;

typedef struct {
  PyObject_HEAD TSPInstance *instance;
} PyTSPInstance;

void free_instance(TSPInstance *instance);
PyObject *PyTSPInstance_New(TSPInstance *instance);
#endif // TSP_INSTANCE_H_