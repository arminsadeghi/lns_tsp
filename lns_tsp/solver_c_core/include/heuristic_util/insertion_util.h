/**
 * @file insertion_util.h
 * @author Armin Sadeghi (a6sadegh@uwaterloo.ca)
 * @brief
 * @version 0.1
 * @date 2023-09-17
 */

#ifndef HEURISTIC_UTIL_INSERTION_UTIL_H_
#define HEURISTIC_UTIL_INSERTION_UTIL_H_

#include "tsp_instance.h"
#include "util/node_dlist.h"
#include <stdbool.h>

typedef struct {
  double cost;
  NodeList *pos;
} Insertion;

double insertion_cost_c(TSPInstance *instance, NodeList *tour, NodeList *node);
Insertion best_insertion_c(TSPInstance *instance, NodeList *tour,
                           NodeList *node);
void insert_node_c(NodeList *prev_node, NodeList *node_to_insert);
#endif // HEURISTIC_UTIL_INSERTION_UTIL_H_
