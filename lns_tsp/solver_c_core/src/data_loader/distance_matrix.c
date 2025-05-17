/**
 * @file distance_matrix.c
 * @author Armin Sadeghi (sadeghiy.armin[at]gmail.com)
 * @version 0.1
 */
#include "data_loader/distance_matrix.h"
#include <Python.h>

void read_distance_matrix(FILE *file, TSPInstance *instance) {
  if (instance->dimension <= 0) {
    fprintf(stderr, "Invalid dimension: %d\n", instance->dimension);
    return;
  }
  instance->distance_matrix = malloc(instance->dimension * sizeof(float *));
  for (int i = 0; i < instance->dimension; i++) {
    instance->distance_matrix[i] = malloc(instance->dimension * sizeof(float));
  }
  if (strcmp(instance->edge_weight_format, "FULL_MATRIX") == 0) {
    for (int i = 0; i < instance->dimension; i++) {
      for (int j = 0; j < instance->dimension; j++) {
        if (fscanf(file, "%f", &instance->distance_matrix[i][j]) != 1) {
          PyErr_Format(PyExc_ValueError,
                       "Failed to read float value for distance_matrix[%d][%d]",
                       i, j);
          fclose(file);
          return;
        }
      }
    }
  } else if (strcmp(instance->edge_weight_format, "UPPER_ROW") == 0) {
    for (int i = 0; i < instance->dimension; i++) {
      instance->distance_matrix[i][i] = 0;
      for (int j = i + 1; j < instance->dimension; j++) {
        if (fscanf(file, "%f", &instance->distance_matrix[i][j]) != 1) {
          PyErr_Format(PyExc_ValueError,
                       "Failed to read float value for distance_matrix[%d][%d]",
                       i, j);
          fclose(file);
          return;
        }
        instance->distance_matrix[j][i] = instance->distance_matrix[i][j];
      }
    }
  } else {
    fprintf(stderr, "Unsupported edge weight type: %s\n",
            instance->edge_weight_type);
  }
}

void create_distance_matrix(TSPInstance *instance) {
  // if edge weight type is EUC_2D fill the distance matrix
  if (strcmp(instance->edge_weight_type, "EUC_2D") == 0) {
    create_distance_matrix_EUC_2D(instance);
  } else if (strcmp(instance->edge_weight_type, "ATT") == 0) {
    create_distance_matrix_ATT(instance);
  } else {
    fprintf(stderr, "Unsupported edge weight type: %s\n",
            instance->edge_weight_type);
  }
}

void create_distance_matrix_EUC_2D(TSPInstance *instance) {
  if (instance->dimension <= 0) {
    fprintf(stderr, "Invalid dimension: %d\n", instance->dimension);
    return;
  }
  instance->distance_matrix = malloc(instance->dimension * sizeof(float *));
  for (int i = 0; i < instance->dimension; i++) {
    instance->distance_matrix[i] = malloc(instance->dimension * sizeof(float));
    for (int j = 0; j < instance->dimension; j++) {
      float dx = instance->nodes[i].x - instance->nodes[j].x;
      float dy = instance->nodes[i].y - instance->nodes[j].y;
      instance->distance_matrix[i][j] = (int)(sqrt(dx * dx + dy * dy) + 0.5);
    }
  }
}

void create_distance_matrix_ATT(TSPInstance *instance) {
  if (instance->dimension <= 0) {
    fprintf(stderr, "Invalid dimension: %d\n", instance->dimension);
    return;
  }
  instance->distance_matrix = malloc(instance->dimension * sizeof(float *));
  for (int i = 0; i < instance->dimension; i++) {
    instance->distance_matrix[i] = malloc(instance->dimension * sizeof(float));
    for (int j = 0; j < instance->dimension; j++) {
      float dx = instance->nodes[i].x - instance->nodes[j].x;
      float dy = instance->nodes[i].y - instance->nodes[j].y;
      float rij = (sqrt(dx * dx + dy * dy) / 10.0);
      int tij = (int)(rij + 0.5);
      if (tij < rij) {
        instance->distance_matrix[i][j] = tij + 1;
      } else {
        instance->distance_matrix[i][j] = tij;
      }
    }
  }
}