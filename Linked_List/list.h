#ifndef LIST_H
#define LIST_H

typedef struct NODE_t {
    double d;
    struct NODE_t *next;
} NODE_t;

void ll_push(NODE_t **list, double a);
double ll_pop(NODE_t **list);
void ll_push_end(NODE_t **list, double a);
double ll_pop_end(NODE_t **list);
#endif
