#include <stdio.h>
#include <stdlib.h>

#include "list.h"

int main(void) {
    NODE_t *head = NULL;

    printf("=== Test 1: Empty list ===\n");
    printf("head = %p\n", (void *)head);

    printf("\n=== Test 2: Push values ===\n");

    ll_push(&head, 10.5);
    printf("Pushed 10.5\n");

    ll_push(&head, 20.5);
    printf("Pushed 20.5\n");

    ll_push(&head, 30.5);
    printf("Pushed 30.5\n");
    ll_push(&head, 40.5);

    printf("Pushed 40.5\n");

    printf("head = %p\n", (void *)head);

    printf("\n=== Test 3: Pop values ===\n");

    printf("Popped: %.2f\n", ll_pop(&head));
    printf("Popped: %.2f\n", ll_pop(&head));
    printf("Popped: %.2f\n", ll_pop(&head));
    printf("Popped: %.2f\n", ll_pop(&head));

    printf("\n=== Test 4: List should now be empty ===\n");
    printf("Popped: %.2f\n", ll_pop(&head));
    printf("head = %p\n", (void *)head);

    printf("\n=== Test 5: pop_at_end ===\n");
    ll_push(&head, 30.5);
    ll_push(&head, 30);
    ll_push(&head, 99);
    printf("Popped: %.2f\n", ll_pop_end(&head));
    printf("Popped: %.2f\n", ll_pop_end(&head));
    return 0;
}
