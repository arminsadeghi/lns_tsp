/**
 * @file tour_util.c
 * @author Armin Sadeghi (a6sadegh@uwaterloo.ca)
 * @version 0.1
 * @date 2023-10-15
 */

#include <stdbool.h>

#include "util/tour_util.h"

void print_tour_dlist(NodeList *tour)
{
    NodeList* current_node = tour;
    while (true)
    {
        printf("%d ", current_node->node);
        current_node = current_node->next;
        if (current_node == tour) break;
    }
}