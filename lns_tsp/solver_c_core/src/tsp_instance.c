/**
 * @file tsp_instance.c
 * @author Armin Sadeghi (sadeghiy.armin[at]gmail.com)
 * @version 0.1
 */

#include "tsp_instance.h"

void free_instance(TSPInstance *instance) {
  if (instance == NULL) {
    return;
  }
  if (instance->distance_matrix != NULL) {
    for (int i = 0; i < instance->dimension; i++) {
      free(instance->distance_matrix[i]);
    }
  }
  if (instance->nodes != NULL) {
    free(instance->nodes);
  }
  free(instance);
}

static void PyTSPInstance_dealloc(PyTSPInstance *self) {
  if (self->instance->distance_matrix != NULL) {
    for (int i = 0; i < self->instance->dimension; i++) {
      free(self->instance->distance_matrix[i]);
    }
    free(self->instance->distance_matrix);
  }
  if (self->instance->nodes != NULL) {
    free(self->instance->nodes);
  }
  if (self->instance) {
    free(self->instance);
  }
  Py_TYPE(self)->tp_free((PyObject *)self);
}

// Expose instance_name to Python
static PyObject *PyTSPInstance_get_instance_name(PyTSPInstance *self,
                                                 void *_closure) {
  (void)_closure; // Unused parameter
  return PyUnicode_FromString(self->instance->instance_name);
}

// Expose dimension to Python
static PyObject *PyTSPInstance_get_dimension(PyTSPInstance *self,
                                             void *_closure) {
  (void)_closure; // Unused parameter
  return PyLong_FromLong(self->instance->dimension);
}

// Expose edge_weight_type to Python
static PyObject *PyTSPInstance_get_edge_weight_type(PyTSPInstance *self,
                                                    void *_closure) {
  (void)_closure; // Unused parameter
  return PyUnicode_FromString(self->instance->edge_weight_type);
}

// Expose edge_weight_format to Python
static PyObject *PyTSPInstance_get_edge_weight_format(PyTSPInstance *self,
                                                      void *_closure) {
  (void)_closure; // Unused parameter
  return PyUnicode_FromString(self->instance->edge_weight_format);
}

// Expose type to Python
static PyObject *PyTSPInstance_get_type(PyTSPInstance *self, void *_closure) {
  (void)_closure; // Unused parameter
  return PyUnicode_FromString(self->instance->type);
}

// List of getters
static PyGetSetDef PyTSPInstance_getsetters[] = {
    {"instance_name", (getter)PyTSPInstance_get_instance_name, NULL,
     "instance name", NULL},
    {"dimension", (getter)PyTSPInstance_get_dimension, NULL, "dimension", NULL},
    {"get_edge_weight_type", (getter)PyTSPInstance_get_edge_weight_type, NULL,
     "edge_weight_type", NULL},
    {"get_edge_weight_format", (getter)PyTSPInstance_get_edge_weight_format,
     NULL, "edge_weight_format", NULL},
    {"get_edge_weight_type", (getter)PyTSPInstance_get_edge_weight_type, NULL,
     "edge_weight_type", NULL},
     {"get_type", (getter)PyTSPInstance_get_type, NULL, "type", NULL},
    {NULL} /* Sentinel */
};

// Define the PyTypeObject
PyTypeObject PyTSPInstance_Type = {
    PyVarObject_HEAD_INIT(NULL, 0).tp_name = "lns_tsp.solver_core.TSPInstance",
    .tp_doc = "TSPInstance object",
    .tp_basicsize = sizeof(PyTSPInstance),
    .tp_flags = Py_TPFLAGS_DEFAULT,
    .tp_dealloc = (destructor)PyTSPInstance_dealloc,
    .tp_getset = PyTSPInstance_getsetters,
};

// Constructor function
PyObject *PyTSPInstance_New(TSPInstance *instance) {
  PyTSPInstance *self = (PyTSPInstance *)PyObject_New(PyTSPInstance, &PyTSPInstance_Type);
  if (!self) {
    free(instance);
    return NULL;
  }
  self->instance = instance;
  return (PyObject *)self;
}