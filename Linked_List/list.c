#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "list.h"

#include <math.h>

void ll_push(NODE_t **list, double a) {
    NODE_t *node = malloc(sizeof *node);
    if (node == NULL) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    node->d = a;
    node->next = *list;
    *list = node;
}

double ll_pop(NODE_t **list) {
    if (*list == NULL) {
        return NAN;
    }
    NODE_t *node = *list;
    double value = node->d;
    *list = node->next;
    free(node);
    return value;
}

void ll_push_end(NODE_t **list, double a) {
    NODE_t *node = malloc(sizeof *node);
    if (node == NULL) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    node->d = a;
    node->next = NULL;
    if (*list == NULL) {
        *list = node;
        return;
    }
    NODE_t *current = *list;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = node;
}

double ll_pop_end(NODE_t **list) {
    if (*list == NULL) {
        return NAN;
    }
    NODE_t *node = *list;
    NODE_t *prev = NULL;
    while (node->next != NULL) {
        prev = node;
        node = node->next;
    }
    double value = node->d;
    if (prev == NULL) {
        *list = NULL;
    } else {
        prev->next = NULL;
    }
    free(node);
}
