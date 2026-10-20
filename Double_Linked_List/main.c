#include "doubleList.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>


static void print_list(DNODE_t **head) {
    uint32_t length = 0;
    double *values = dll_export(*head, &length);
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
    DNODE_t *head = NULL;
    DNODE_t *tail = NULL;

    printf("\nTest 1: Push values\n");

    dll_push(&head, &tail, 10.5);
    printf("Pushed 10.5\n");
    print_list(&head);

    dll_push(&head, &tail, 20.5);
    printf("Pushed 20.5\n");
    print_list(&head);

    dll_push(&head, &tail, 30.5);
    printf("Pushed 30.5\n");
    print_list(&head);

    dll_push(&head, &tail, 40.5);
    printf("Pushed 40.5\n");
    print_list(&head);

    printf("\nTest 2: Pop values\n");

    printf("Popped: %.2f\n", dll_pop(&head, &tail));
    print_list(&head);
    printf("Popped: %.2f\n", dll_pop(&head, &tail));
    print_list(&head);
    printf("Popped: %.2f\n", dll_pop(&head, &tail));
    print_list(&head);
    printf("Popped: %.2f\n", dll_pop(&head, &tail));
    print_list(&head);

    printf("\nTest 3: Empty List\n");
    printf("Popped: %.2f\n", dll_pop(&head, &tail));
    printf("Popped at end: %.2f\n", dll_pop_end(&head, &tail));
    printf("head = %p, tail = %p\n", (void *)head, (void *)tail);

    printf("\nTest 4: push_end\n");
    dll_push_end(&head, &tail, 10.5);
    printf("Pushed at end 10.5\n");
    print_list(&head);
    dll_push_end(&head, &tail, 20.5);
    printf("Pushed at end 20.5\n");
    print_list(&head);
    dll_push_end(&head, &tail, 30.5);
    printf("Pushed at end 30.5\n");
    print_list(&head);

    printf("\nTest 5: pop_at_end\n");
    printf("Popped: %.2f\n", dll_pop_end(&head, &tail));
    print_list(&head);
    printf("Popped: %.2f\n", dll_pop_end(&head, &tail));
    print_list(&head);
    printf("Popped: %.2f\n", dll_pop_end(&head, &tail));
    print_list(&head);
    printf("Popped: %.2f\n", dll_pop_end(&head, &tail));

    printf("\nTest 6: dll_find_num\n");
    dll_push(&head, &tail, 10.5);
    dll_push(&head, &tail, 30);
    dll_push(&head, &tail, 99);
    print_list(&head);
    DNODE_t *found = dll_find_num(head, 10.5);
    if (found != NULL) {
        printf("Found: %.2f\n", found->d);
    } else {
        printf("Not found: 10.50\n");
    }
    found = dll_find_num(head, 55.5);
    if (found != NULL) {
        printf("Found: %.2f\n", found->d);
    } else {
        printf("Not found: 55.50\n");
    }
    dll_clear(&head, &tail);
    printf("Popped: %.2f\n", dll_pop(&head, &tail));

    printf("\nTest 7: dll_del_index\n");
    printf("Deleted: %d\n", dll_del_index(&head, &tail, 0));
    dll_push(&head, &tail, 10.5);
    dll_push(&head, &tail, 30);
    dll_push(&head, &tail, 99);
    dll_push(&head, &tail, 5.5);
    print_list(&head);
    printf("Deleted at 1: %d\n", dll_del_index(&head, &tail, 1));
    print_list(&head);
    printf("Deleted at 0: %d\n", dll_del_index(&head, &tail, 0));
    print_list(&head);
    printf("Deleted at 7: %d\n", dll_del_index(&head, &tail, 7));
    print_list(&head);
    printf("Deleted at 1: %d\n", dll_del_index(&head, &tail, 1));
    print_list(&head);
    dll_clear(&head, &tail);

    printf("\nTest 8: dll_export\n");
    dll_push(&head, &tail, 10.5);
    dll_push(&head, &tail, 20.5);
    dll_push(&head, &tail, 30.5);
    dll_push(&head, &tail, 40.5);

    uint32_t length = 0;
    double *exported_values = dll_export(head, &length);
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

    printf("\nTest 9: dll_clear\n");
    dll_clear(&head, &tail);
    print_list(&head);
    printf("head = %p, tail = %p\n", (void *)head, (void *)tail);

    printf("\nTest 10: Benchmark\n");
    uint32_t const MAX_I = 40000;

    printf("push (%u)\n", (unsigned)MAX_I);
    clock_t start = clock();
    for (uint32_t i = 0; i < MAX_I; i++) {
        dll_push(&head, &tail, i);
    }
    clock_t end = clock();
    printf("time (s): %f\n", (double)(end - start) / CLOCKS_PER_SEC);

    printf("pop (%u)\n", (unsigned)MAX_I);
    start = clock();
    for (uint32_t i = 0; i < MAX_I; i++) {
        dll_pop(&head, &tail);
    }
    end = clock();
    printf("time (s): %f\n", (double)(end - start) / CLOCKS_PER_SEC);

    printf("push_end (%u)\n", (unsigned)MAX_I);
    start = clock();
    for (uint32_t i = 0; i < MAX_I; i++) {
        dll_push_end(&head, &tail, i);
    }
    end = clock();
    printf("time (s): %f\n", (double)(end - start) / CLOCKS_PER_SEC);

    printf("pop_end (%u)\n", (unsigned)MAX_I);
    start = clock();
    for (uint32_t i = 0; i < MAX_I; i++) {
        dll_pop_end(&head, &tail);
    }
    end = clock();
    printf("time (s): %f\n", (double)(end - start) / CLOCKS_PER_SEC);

    printf("repopulating, please wait...\n");

    for (uint32_t i = 0; i < MAX_I; i++) {
        dll_push(&head, &tail, i);
    }

    printf("find_middle (%u)\n", (unsigned)MAX_I);
    start = clock();
    for (uint32_t i = 0; i < MAX_I; i++) {
        dll_find_num(head, MAX_I / 2);
    }
    end = clock();
    printf("time (s): %f\n", (double)(end - start) / CLOCKS_PER_SEC);

    printf("del_middle (%u)\n", (unsigned)MAX_I);
    start = clock();
    for (uint32_t i = 0; i < MAX_I; i++) {
        dll_del_index(&head, &tail, (MAX_I - i) / 2);
    }
    end = clock();
    printf("time (s): %f\n", (double)(end - start) / CLOCKS_PER_SEC);

    dll_clear(&head, &tail);
    return 0;
}
