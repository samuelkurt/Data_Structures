#ifndef DOUBLELIST_H
#define DOUBLELIST_H

#include <stdint.h>

typedef struct DNODE_t {
    double d;
    struct DNODE_t *next;
    struct DNODE_t *past;
} DNODE_t;

void    dll_push(DNODE_t **head, DNODE_t **tail, double value);
double  dll_pop(DNODE_t **head, DNODE_t **tail);
void    dll_push_end(DNODE_t **head, DNODE_t **tail, double value);
double dll_pop_end(DNODE_t **list, DNODE_t **tail);
DNODE_t *dll_find_num(DNODE_t *list, double d);
int dll_del_index(DNODE_t **list, DNODE_t **tail, uint32_t d);
void dll_clear(DNODE_t **list, DNODE_t **tail);
double* dll_export(DNODE_t *list, uint32_t* count);

#endif
