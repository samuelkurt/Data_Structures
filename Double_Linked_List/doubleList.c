#include "doubleList.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void dll_push(DNODE_t **list, DNODE_t **tail, double a) {
    DNODE_t *node = malloc(sizeof *node);
    if (node == NULL) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    node->d = a;
    node->next = *list;
    node->past = NULL;
    if (*list != NULL) {
        (*list)->past = node;
    } else {
        *tail = node;
    }
    *list = node;
}

double dll_pop(DNODE_t **list, DNODE_t **tail) {
    if (*list == NULL) {
        return NAN;
    }
    DNODE_t *node = *list;
    double value = node->d;
    *list = node->next;
    if (*list != NULL) {
        (*list)->past = NULL;
    } else {
        *tail = NULL;
    }
    free(node);
    return value;
}

void dll_push_end(DNODE_t **list, DNODE_t **tail, double a) {
    DNODE_t *node = malloc(sizeof *node);
    if (node == NULL) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    node->d = a;
    node->next = NULL;
    node->past = *tail;
    if (*list == NULL) {
        *list = node;
        *tail = node;
        return;
    }
    (*tail)->next = node;
    *tail = node;
}

double dll_pop_end(DNODE_t **list, DNODE_t **tail) {
    if (*list == NULL) {
        return NAN;
    }
    DNODE_t *node = *tail;
    DNODE_t *prev = node->past;
    double value = node->d;
    if (prev == NULL) {
        *list = NULL;
    } else {
        prev->next = NULL;
    }
    *tail = prev;
    free(node);
    return value;
}

DNODE_t *dll_find_num(DNODE_t *list, double d) {
    if (list == NULL) {
        return NULL;
    }
    DNODE_t *node = list;
    while (node != NULL && node->d != d) {
        node = node->next;
    }
    return node;
}

int dll_del_index(DNODE_t **list, DNODE_t **tail, uint32_t d) {
    if (*list == NULL) {
        return -1;
    }
    DNODE_t *node = *list;
    DNODE_t *prev = NULL;
    uint32_t i = 0;
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
    if (node->next == NULL) {
        *tail = prev;
    } else {
        node->next->past = prev;
    }
    free(node);
    return 0;
}

void dll_clear(DNODE_t **list, DNODE_t **tail) {
    if (*list == NULL) {
        return;
    }
    DNODE_t *node = *list;
    while (node != NULL) {
        DNODE_t *next = node->next;
        free(node);
        node = next;
    }
    *list = NULL;
    *tail = NULL;
}

double* dll_export(DNODE_t *list, uint32_t* count) {
    if (list == NULL) {
        *count = 0;
        return NULL;
    }
    DNODE_t *node = list;
    *count = 0;
    while (node != NULL) {
        node = node->next;
        (*count)++;
    }
    double *values = malloc(*count * sizeof(double));
    if (values == NULL) {
        *count = 0;
        return NULL;
    }
    node = list;
    uint32_t i = 0;
    while (node != NULL) {
        values[i] = node->d;
        node = node->next;
        i++;
    }
    return values;
}
