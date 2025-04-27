/**
 * @file distance_matrix.h
 * @author Armin Sadeghi (sadeghiy.armin[at]gmail.com)
 * @version 0.1
 */

#ifndef DATA_LOADER_DISTANCE_MATRIX_H_
#define DATA_LOADER_DISTANCE_MATRIX_H_
#include "tsp_instance.h"
#include <stdio.h>

void create_distance_matrix(TSPInstance *instance);
void create_distance_matrix_EUC_2D(TSPInstance *instance);
void read_distance_matrix(FILE *file, TSPInstance *instance);

#endif // DATA_LOADER_DISTANCE_MATRIX_H_