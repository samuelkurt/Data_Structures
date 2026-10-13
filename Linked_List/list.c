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
    return value;
}

NODE_t *ll_find_num(NODE_t **list, const double d) {
    if (*list == NULL) {
        return NULL;
    }
    NODE_t *node = *list;
    while (node != NULL && node->d != d) {
        node = node->next;
    }
    return node;
}

int ll_del_num(NODE_t **list, const uint32_t d) {
    if (*list == NULL) {
        return -1;
    }
    NODE_t *node = *list;
    NODE_t *prev = NULL;
    int i = 0;
    while (node != NULL && i != d) {
        prev = node;
        node = node->next;
        i++;
    }
    if (node == NULL) {
        return -2;
    }
    if (prev == NULL) {
        *list = node->next;
    } else {
        prev->next = node->next;
    }
    free(node);
    return 0;
}

void ll_clear(NODE_t **list) {
    if (*list == NULL) {

    }
    NODE_t *node = *list;
    while (node != NULL) {
        NODE_t *next = node->next;
        free(node);
        node = next;
    }
    *list = NULL;
}

double* ll_export(NODE_t **list, uint32_t* count) {
    if (*list == NULL) {
        *count = 0;
        return NULL;
    }
    NODE_t *node = *list;
    *count = 0;
    while (node != NULL) {
        node = node->next;
        (*count)++;
    }
    double *values = malloc(*count * sizeof(double));
    if (values == NULL) {
        return NULL;
    }
    node = *list;
    int i = 0;
    while (node != NULL) {
        values[i] = node->d;
        NODE_t *temp = node;
        node = node->next;
        i++;
    }
    return values;
}

