/**
 * @file node_dlist.c
 * @author Armin Sadeghi (a6sadegh@uwaterloo.ca)
 * @version 0.1
 * @date 2023-10-14
 * @copyright Copyright (c) 2023
 */

#include <stdio.h>
#include <float.h>
#include <stdlib.h>
#include <stdbool.h>

#include "util/node_dlist.h"


NodeList* create_node_list(int* tour, int tour_length, int loop)
{
    NodeList* node_list = malloc(sizeof(NodeList));
    node_list->node = tour[0];
    node_list->next = NULL;
    node_list->prev = NULL;
    NodeList* current = node_list;
    for (int i = 1; i < tour_length; ++i) {
        NodeList* new_node = malloc(sizeof(NodeList));
        new_node->node = tour[i];
        new_node->next = NULL;
        new_node->prev = current;
        current->next = new_node;
        current = new_node;
    }
    if (loop){
        node_list->prev = current;
        current->next = node_list;
    }
    return node_list;
}

NodeList* create_node_list_from_python_list(PyObject* tour, int tour_length, int loop)
{
    NodeList* node_list = malloc(sizeof(NodeList));
    node_list->node = PyLong_AsLong(PyList_GetItem(tour, 0));
    node_list->next = NULL;
    node_list->prev = NULL;
    NodeList* current = node_list;
    for (int i = 1; i < tour_length; ++i) {
        NodeList* new_node = malloc(sizeof(NodeList));
        new_node->node = PyLong_AsLong(PyList_GetItem(tour, i));
        new_node->next = NULL;
        new_node->prev = current;
        current->next = new_node;
        current = new_node;
    }

    if (loop) {
        node_list->prev = current;
        current->next = node_list;
    }
    return node_list;
}

void free_node_list(NodeList* node_list)
{
    NodeList* current = node_list;
    while (true) {
        NodeList* next = current->next;
        free(current);
        current = next;
        if (current == NULL || current == node_list) break;
    }
}