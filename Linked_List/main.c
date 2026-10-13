#include "list.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>


static void print_list(NODE_t **head) {
    uint32_t length = 0;
    double *values = ll_export(head, &length);
    printf("List: [");
    for (uint32_t i = 0; i < length; i++) {
        if (i > 0) {
            printf(", ");
        }
        printf("%.2f", values[i]);
    }
    printf("]\n");
    free(values);
}

int main(void) {
    NODE_t *head = NULL;

    printf("\nTest 1: Push values\n");

    ll_push(&head, 10.5);
    printf("Pushed 10.5\n");
    print_list(&head);

    ll_push(&head, 20.5);
    printf("Pushed 20.5\n");
    print_list(&head);

    ll_push(&head, 30.5);
    printf("Pushed 30.5\n");
    print_list(&head);

    ll_push(&head, 40.5);
    printf("Pushed 40.5\n");
    print_list(&head);

    printf("head = %p\n", (void *)head);

    printf("\nTest 2: Pop values\n");

    printf("Popped: %.2f\n", ll_pop(&head));
    print_list(&head);
    printf("Popped: %.2f\n", ll_pop(&head));
    print_list(&head);
    printf("Popped: %.2f\n", ll_pop(&head));
    print_list(&head);
    printf("Popped: %.2f\n", ll_pop(&head));
    print_list(&head);

    printf("\nTest 3: Empty List\n");
    printf("Popped: %.2f\n", ll_pop(&head));
    printf("Popped at end: %.2f\n", ll_pop_end(&head));
    printf("head = %p\n", (void *)head);

    printf("\nTest 4: push_end\n");
    ll_push_end(&head, 10.5);
    printf("Pushed at end 10.5\n");
    print_list(&head);
    ll_push_end(&head, 20.5);
    printf("Pushed at end 20.5\n");
    print_list(&head);
    ll_push_end(&head, 30.5);
    printf("Pushed at end 30.5\n");
    print_list(&head);

    printf("\nTest 5: pop_at_end\n");
    printf("Popped: %.2f\n", ll_pop_end(&head));
    print_list(&head);
    printf("Popped: %.2f\n", ll_pop_end(&head));
    print_list(&head);
    printf("Popped: %.2f\n", ll_pop_end(&head));
    print_list(&head);
    printf("Popped: %.2f\n", ll_pop_end(&head));

    printf("\nTest 6: ll_find_num\n");
    ll_push(&head, 10.5);
    ll_push(&head, 30);
    ll_push(&head, 99);
    print_list(&head);
    NODE_t *found = ll_find_num(&head, 10.5);
    if (found != NULL) {
        printf("Found: %.2f\n", found->d);
    } else {
        printf("Not found: 10.50\n");
    }
    found = ll_find_num(&head, 55.5);
    if (found != NULL) {
        printf("Found: %.2f\n", found->d);
    } else {
        printf("Not found: 55.50\n");
    }
    ll_clear(&head);
    printf("Popped: %.2f\n", ll_pop(&head));

    printf("\nTest 7: ll_del_num\n");
    printf("Deleted: %d\n", ll_del_index(&head, 0));
    ll_push(&head, 10.5);
    ll_push(&head, 30);
    ll_push(&head, 99);
    ll_push(&head, 5.5);
    print_list(&head);
    printf("Deleted at 1: %d\n", ll_del_index(&head, 1));
    print_list(&head);
    printf("Deleted at 0: %d\n", ll_del_index(&head, 0));
    print_list(&head);
    printf("Deleted at 7: %d\n", ll_del_index(&head, 7));
    print_list(&head);
    printf("Deleted at 1: %d\n", ll_del_index(&head, 1));
    print_list(&head);
    ll_clear(&head);

    printf("\nTest 8: ll_export\n");
    ll_push(&head, 10.5);
    ll_push(&head, 20.5);
    ll_push(&head, 30.5);
    ll_push(&head, 40.5);

    uint32_t length = 0;
    double *exported_values = ll_export(&head, &length);
    if (exported_values != NULL) {
        printf("Exported values: ");
        for (uint32_t i = 0; i < length; i++) {
            printf("%.2f ", exported_values[i]);
        }
        printf("\nLength: %u\n", (unsigned)length);
        free(exported_values);
    } else {
        printf("Failed to export values.\n");
    }
    print_list(&head);

    printf("\nTest 9: ll_clear\n");
    ll_clear(&head);
    print_list(&head);
    printf("head = %p\n", (void *)head);

    printf("\nTest 10: Benchmark\n");
    uint32_t const MAX_I = 100000;

    printf("push (%u)\n", (unsigned)MAX_I);
    clock_t start = clock();
    for (uint32_t i = 0; i < MAX_I; i++) {
        ll_push(&head, i);
    }
    clock_t end = clock();
    printf("time (s): %f\n", (double)(end - start) / CLOCKS_PER_SEC);

    printf("pop (%u)\n", (unsigned)MAX_I);
    start = clock();
    for (uint32_t i = 0; i < MAX_I; i++) {
        ll_pop(&head);
    }
    end = clock();
    printf("time (s): %f\n", (double)(end - start) / CLOCKS_PER_SEC);

    printf("push_end (%u)\n", (unsigned)MAX_I);
    start = clock();
    for (uint32_t i = 0; i < MAX_I; i++) {
        ll_push_end(&head, i);
    }
    end = clock();
    printf("time (s): %f\n", (double)(end - start) / CLOCKS_PER_SEC);

    printf("pop_end (%u)\n", (unsigned)MAX_I);
    start = clock();
    for (uint32_t i = 0; i < MAX_I; i++) {
        ll_pop_end(&head);
    }
    end = clock();
    printf("time (s): %f\n", (double)(end - start) / CLOCKS_PER_SEC);

    printf("repopulating, please wait...\n");

    for (uint32_t i = 0; i < MAX_I; i++) {
        ll_push(&head, i);
    }

    printf("find_middle (%u)\n", (unsigned)MAX_I);
    start = clock();
    for (uint32_t i = 0; i < MAX_I; i++) {
        ll_find_num(&head, MAX_I / 2);
    }
    end = clock();
    printf("time (s): %f\n", (double)(end - start) / CLOCKS_PER_SEC);

    printf("del_middle (%u)\n", (unsigned)MAX_I);
    start = clock();
    for (uint32_t i = 0; i < MAX_I; i++) {
        ll_del_index(&head, (MAX_I - i) / 2);
    }
    end = clock();
    printf("time (s): %f\n", (double)(end - start) / CLOCKS_PER_SEC);

    ll_clear(&head);
    return 0;
}