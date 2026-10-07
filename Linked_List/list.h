#ifndef LIST_H
#define LIST_H

typedef struct NODE_t {
    double d;
    struct NODE_t *next;
} NODE_t;

void    ll_push(NODE_t **head, double value);
double  ll_pop(NODE_t **head);
void    ll_push_end(NODE_t **head, double value);
double ll_pop_end(NODE_t **list);
NODE_t *ll_find_num(NODE_t **list, const double d);
NODE_t *ll_del_num(NODE_t **list, const int d);
NODE_t *ll_clear(NODE_t **list);

#endif