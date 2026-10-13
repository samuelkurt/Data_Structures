#ifndef LIST_H
#define LIST_H

#include <stdint.h>

typedef struct NODE_t {
    double d;
    struct NODE_t *next;
} NODE_t;

void    ll_push(NODE_t **head, double value);
double  ll_pop(NODE_t **head);
void    ll_push_end(NODE_t **head, double value);
double ll_pop_end(NODE_t **list);
NODE_t *ll_find_num(NODE_t *list, double d);
int ll_del_index(NODE_t **list, uint32_t d);
void ll_clear(NODE_t **list);
double* ll_export(NODE_t **list, uint32_t* count);

#endif