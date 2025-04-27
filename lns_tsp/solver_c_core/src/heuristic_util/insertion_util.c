/**
 * @file insertion_util.c
 * @author Armin Sadeghi (a6sadegh@uwaterloo.ca)
 * @brief
 * @version 0.1
 * @date 2023-09-17
 */
#include "heuristic_util/insertion_util.h"
#include "util/node_dlist.h"

#include <float.h>
#include <stdio.h>
#include <stdlib.h>

/**
    Calculates the cost of inserting a node in a tour at a given position.
    Returns the cost.
 */
double insertion_cost_c(TSPInstance *instance, NodeList *tour, NodeList *node) {
  double cost = 0;
  int prev = tour->node;
  int next = tour->next->node;
  int current = node->node;
  cost += instance->distance_matrix[prev][current];
  cost += instance->distance_matrix[current][next];
  cost -= instance->distance_matrix[prev][next];
  return cost;
}

/**
    Finds the best insertion position for a node in a tour.
    Returns the insertion cost and the position.
 */
Insertion best_insertion_c(TSPInstance *instance, NodeList *tour,
                           NodeList *node) {
  double best_cost = DBL_MAX;
  NodeList *best_pos = NULL;
  NodeList *current_node = tour;
  while (true) {
    double cost = insertion_cost_c(instance, current_node, node);
    if (cost < best_cost) {
      best_cost = cost;
      best_pos = current_node;
    }
    current_node = current_node->next;
    if (current_node == tour)
      break;
  }
  Insertion insertion;
  insertion.cost = best_cost;
  insertion.pos = best_pos;
  return insertion;
}

void insert_node_c(NodeList *prev_node, NodeList *node_to_insert) {
  // Create a new node
  NodeList *node = malloc(sizeof(NodeList));
  node->node = node_to_insert->node;
  NodeList *next_node = prev_node->next;
  prev_node->next = node;
  node->prev = prev_node;
  node->next = next_node;
  next_node->prev = node;
}

NodeList *remove_and_free_node_c(NodeList *node) {
  NodeList *prev_node = node->prev;
  NodeList *next_node = node->next;
  if (prev_node == NULL || next_node == NULL) {
    return NULL;
  }
  if (prev_node == next_node) {
    prev_node->next = NULL;
    prev_node->prev = NULL;
  } else {
    prev_node->next = next_node;
    next_node->prev = prev_node;
  }
  free(node);
  return prev_node;
}
