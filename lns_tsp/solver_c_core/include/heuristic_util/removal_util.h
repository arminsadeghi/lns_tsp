/**
 * @file removal_util.h
 * @author Armin Sadeghi (a6sadegh@uwaterloo.ca)
 * @version 0.1
 * @date 2023-10-08
 * @copyright Copyright (c) 2023
 */

#ifndef SOLVER_INCLUDE_HEURISTIC_UTIL_REMOVE_UTIL_H_
#define SOLVER_INCLUDE_HEURISTIC_UTIL_REMOVE_UTIL_H_
#include "tsp_instance.h"

double removal_cost_c(TSPInstance *instance, int *tour, int tour_length,
                      int node);
#endif // SOLVER_INCLUDE_HEURISTIC_UTIL_REMOVE_UTIL_H_
