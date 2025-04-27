/**
 * @file removal_util.c
 * @author Armin Sadeghi (a6sadegh@uwaterloo.ca)
 * @version 0.1
 * @date 2023-10-08
 * @copyright Copyright (c) 2023
 */

#include "heuristic_util/removal_util.h"

double removal_cost_c(TSPInstance *instance, int *tour, int tour_length,
                      int city) {
  if (tour[city] == -1)
    return 0;

  double cost = 0;
  int prev_city_index = city - 1;
  int next_city_index = city + 1;

  if (prev_city_index == -1)
    prev_city_index = tour_length - 1;
  if (next_city_index == tour_length)
    next_city_index = 0;

  while (tour[prev_city_index] == -1) {
    prev_city_index--;
    if (prev_city_index == -1)
      return 0;
  }

  while (tour[next_city_index] == -1) {
    next_city_index++;
    if (next_city_index == tour_length)
      return 0;
  }

  int prev_city = tour[prev_city_index];
  int next_city = tour[next_city_index];
  cost += instance->distance_matrix[prev_city][tour[city]];
  cost += instance->distance_matrix[tour[city]][next_city];
  cost -= instance->distance_matrix[prev_city][next_city];
  return cost;
}