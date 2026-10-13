#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <MATH.h>

#include "doubleList.h"

int main(void) {
    NODE_t *head = NULL;

    printf("\n=== Test 2: Push values ===\n");

    ll_push(&head, 10.5);
    printf("Pushed 10.5\n");
    ll_push(&head, 20.5);
    printf("Pushed 20.5\n");
    ll_push(&head, 30.5);
    printf("Pushed 30.5\n");
    ll_push(&head, 40.5);
    printf("Pushed 40.5\n");
    printf("head = %p\n", (void *)head->next);
    printf("tail = %p\n", (void *)head->past);

    printf("\n=== Test 3: Pop values ===\n");

    printf("Backward traversal:\n");
    while (head->past != NULL) {
        printf("%f\n", head->past->d);
        head->past = head->past->past;
    }
    return 0;
}

   /* printf("\n=== Test 4: Empty List ===\n");
    printf("Popped: %.2f\n", ll_pop(&head));
    printf("head = %p\n", (void *)head);

    printf("\n=== Test 5: pop_at_end ===\n");
    ll_push(&head, 30.5);
    ll_push(&head, 30);
    ll_push(&head, 99);
    printf("Popped: %f\n", ll_pop_end(&head));
    printf("Popped: %f\n", ll_pop_end(&head));
    printf("Popped: %f\n", ll_pop_end(&head));
    printf("Popped: %f\n", ll_pop_end(&head));

    printf("\n=== Test 6: ll_find_num ===\n");
    ll_push(&head, 10.5);
    ll_push(&head, 30);
    ll_push(&head, 99);
    printf("Popped: %p\n", ll_find_num(&head, 10.5));
    ll_clear(&head);
    printf("Popped: %.2f\n", ll_pop(&head));

    printf("\n=== Test 7: ll_del_num ===\n");
    ll_push(&head, 10.5);
    ll_push(&head, 30);
    ll_push(&head, 99);
    printf("Popped: %p\n", ll_del_num(&head, 1));
    printf("Popped: %.2f\n", ll_pop(&head));
    printf("Popped: %.2f\n", ll_pop(&head));
    printf("Popped: %.2f\n", ll_pop(&head));

    printf("\n=== Test 8: ll_export ===\n");
    ll_push(&head, 10.5);
    ll_push(&head, 20.5);
    ll_push(&head, 30.5);
    ll_push(&head, 40.5);

    double *exported_values = ll_export(&head);
    if (exported_values != NULL) {
        printf("Exported values: ");
        for (int i = 0; i < 4; i++) {
            printf("%.2f ", exported_values[i]);
        }
        printf("\n");
        free(exported_values);
    } else {
        printf("Failed to export values.\n");
    }

    printf("\n=== Test 9: Benchmakr ===\n");
    printf("push\n");
    long start = clock();
    int const MAX_I = 100000;
    for (int i = 0; i < MAX_I; i++) {
        ll_push(&head, i);
    }
    long end = clock();
    printf("time (s): %f\n", (double)(end - start) / CLOCKS_PER_SEC);

    printf("pop\n");
    start = clock();
    for (int i = 0; i < MAX_I; i++) {
        ll_pop(&head);
    }
    end = clock();
    printf("time (s): %f\n", (double)(end - start) / CLOCKS_PER_SEC);

    printf("push_end\n");
    start = clock();
    for (int i = 0; i < MAX_I; i++) {
        ll_push_end(&head, i);
    }
    end = clock();
    printf("time (s): %f\n", (double)(end - start) / CLOCKS_PER_SEC);

    printf("pop_end\n");
    start = clock();
    for (int i = 0; i < MAX_I; i++) {
        ll_pop_end(&head);
    }
    end = clock();
    printf("time (s): %f\n", (double)(end - start) / CLOCKS_PER_SEC);

    printf("repopulating, please wait...\n");

    for (int i = 0; i < MAX_I; i++) {
        ll_push(&head, i);
    }

    printf("pop_end\n");
    start = clock();
    for (int i = 0; i < MAX_I; i++) {
        ll_pop_end(&head);
    }
    end = clock();
    printf("time (s): %f\n", (double)(end - start) / CLOCKS_PER_SEC);

    printf("repopulating, please wait...\n");

    for (int i = 0; i < MAX_I; i++) {
        ll_push(&head, i);
    }

    printf("find_random\n");
    start = clock();
    srand(time(NULL));
    for (int i = 0; i < MAX_I; i++) {
        int n = 0;
        NODE_t *node = head;
        while (node != NULL) {
            n++;
            node = node->next;
        }
        int random_index = rand() % n;
        ll_find_num(&head, random_index);
    }
    end = clock();
    printf("time (s): %f\n", (double)(end - start) / CLOCKS_PER_SEC);

    printf("del_random\n");
    start = clock();
    srand(time(NULL));
    for (int i = 0; i < MAX_I; i++) {
        int n = 0;
        NODE_t *node = head;
        while (node != NULL) {
            n++;
            node = node->next;
        }
        int random_index = rand() % n;
        ll_del_num(&head, random_index);
    }
    end = clock();
    printf("time (s): %f\n", (double)(end - start) / CLOCKS_PER_SEC);
    return 0;
}
*/