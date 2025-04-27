/**
 * @file load_instance.c
 * @author Armin Sadeghi (sadeghiy.armin[at]gmail.com)
 * @version 0.1
 */

#include "data_loader/load_instance.h"
#include <Python.h>
#include <string.h>

#define MAX_LINE 256

FILE *open_file(const char *filename) {
  FILE *file = fopen(filename, "r");
  if (!file) {
    perror("Failed to open file");
    return NULL;
  }
  return file;
}

void read_file(FILE *file, TSPInstance *instance) {
  char line[MAX_LINE];
  while (fgets(line, sizeof(line), file)) {
    if (strncmp(line, "NAME", 4) == 0) {
      sscanf(line, "NAME : %s", instance->instance_name);
    } else if (strncmp(line, "DIMENSION", 9) == 0) {
      sscanf(line, "DIMENSION : %d", &instance->dimension);
    } else if (strncmp(line, "TYPE", 4) == 0) {
      sscanf(line, "TYPE : %s", instance->type);
    } else if (strncmp(line, "EDGE_WEIGHT_TYPE", 16) == 0) {
      sscanf(line, "EDGE_WEIGHT_TYPE : %s", instance->edge_weight_type);
    } else if (strncmp(line, "EDGE_WEIGHT_FORMAT", 17) == 0) {
      sscanf(line, "EDGE_WEIGHT_FORMAT : %s", instance->edge_weight_format);
    } else if (strncmp(line, "NODE_COORD_SECTION", 18) == 0) {
      read_node_section(file, instance);
    } else if (strncmp(line, "DISPLAY_DATA_SECTION", 20) == 0) {
      read_node_section(file, instance);
    } else if (strncmp(line, "EDGE_WEIGHT_SECTION", 18) == 0) {
      read_distance_matrix(file, instance);
    } else if (strncmp(line, "EOF", 3) == 0) {
      break; // End of header section
    }
  }
}

void print_instance(const TSPInstance *instance) {
  printf("Instance Name: %s\n", instance->instance_name);
  printf("Type: %s\n", instance->type);
  printf("Dimension: %d\n", instance->dimension);
  printf("Edge Weight Type: %s\n", instance->edge_weight_type);
  printf("Edge Weight Format: %s\n", instance->edge_weight_format);
}

int read_instance_from_file(TSPInstance *instance, char *filename) {
  FILE *file = open_file(filename);
  if (!file) {
    fprintf(stderr, "Error opening file: %s\n", filename);
    return 1;
  }
  read_file(file, instance);
  if (instance->distance_matrix == NULL) {
    create_distance_matrix(instance);
  }
  return 0;
}

void read_node_section(FILE *file, TSPInstance *instance) {
  if (instance->dimension <= 0) {
    fprintf(stderr, "Invalid dimension: %d\n", instance->dimension);
    return;
  }
  char line[MAX_LINE];
  instance->nodes = malloc(instance->dimension * sizeof(Node));
  for (int i = 0; i < instance->dimension; i++) {
    fgets(line, sizeof(line), file);
    sscanf(line, "%d %f %f", &instance->nodes[i].id, &instance->nodes[i].x,
           &instance->nodes[i].y);
    instance->nodes[i].id--;
  }
}

extern PyObject *read_instance_from_file_py(PyObject *self, PyObject *args) {
  PyObject *filename;
  if (!PyArg_ParseTuple(args, "O", &filename)) {
    return NULL;
  }
  char *filename_str = PyUnicode_AsUTF8(filename);
  if (!filename_str) {
    return NULL;
  }
  TSPInstance *instance = malloc(sizeof(TSPInstance));
  instance->dimension = 0;
  instance->nodes = NULL;
  instance->distance_matrix = NULL;
  instance->instance_name[0] = '\0';
  instance->type[0] = '\0';
  instance->edge_weight_type[0] = '\0';
  instance->edge_weight_format[0] = '\0';
  instance->edge_weight_type[0] = '\0';
  instance->edge_weight_format[0] = '\0';
  instance->edge_weight_type[0] = '\0';
  instance->edge_weight_format[0] = '\0';
  read_instance_from_file(instance, filename_str);
  PyTSPInstance *py_instance = PyTSPInstance_New(instance);
  if (!py_instance) {
    free(instance);
    return NULL;
  }
  return (PyObject *)py_instance;
}