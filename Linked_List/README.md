# Singly Linked List (LL)

A singly linked list of `double` values in C99. It has **only a head pointer**.
Part of the list performance comparison project (LL vs. DLL).

## Files

| File | Purpose |
|---|---|
| `list.h`, `list.c` | The library, all functions use the prefix `ll_` |
| `main.c` | Fully automatic test program: validation, then benchmark |

## Build and run

```
gcc -std=c99 -O2 main.c list.c -o ll
./ll
```

`CMakeLists.txt` is included as well (it requires CMake 4.3 or newer).

## Functions

| Function | What it does | Returns |
|---|---|---|
| `ll_push(&head, v)` | Insert at the front | nothing |
| `ll_push_end(&head, v)` | Append at the end | nothing |
| `ll_pop(&head)` | Remove the first element | its value, `NAN` if the list is empty |
| `ll_pop_end(&head)` | Remove the last element | its value, `NAN` if the list is empty |
| `ll_find_num(head, v)` | Search for the first node with value `v` | pointer to it, `NULL` if not found |
| `ll_del_index(&head, i)` | Remove the element at index `i` | `0` ok, `-1` list empty, `-2` index out of range |
| `ll_export(&head, &count)` | Copy all values into a new array | the array (caller must `free` it), `NULL` if empty |
| `ll_clear(&head)` | Free all nodes, `head` becomes `NULL` | nothing |

The list only holds numbers, so `NAN` is never a valid element and can safely
signal "no value" when popping from an empty list.

## Why some operations are fast and others slow

Each node only knows its successor, and the list only knows its first node.

| Operation | Cost | Reason |
|---|---|---|
| `ll_push`, `ll_pop` | O(1) | The head is right there |
| `ll_push_end` | O(n) | No tail pointer: walk from the head to the last node |
| `ll_pop_end` | O(n) | Walk to the second-to-last node so it can be unlinked |
| `ll_find_num`, `ll_del_index` | O(n) | Walk until the value or index is reached |

A tail pointer alone would make appending O(1), but removing the last node of
a singly linked list would still need a walk to find its predecessor. That is
what the `prev` pointer of a doubly linked list removes.

## Benchmark

`main.c` runs every scenario with the same `MAX_I`, so the times are directly
comparable. There is no `printf` inside the timed loops, time is measured with
`clock()`.

Expect `push` and `pop` to finish in a fraction of a millisecond, while
`push_end`, `pop_end`, `find_middle` and `del_middle` take orders of magnitude
longer. Every one of those calls walks a list that is up to `MAX_I` nodes long,
so their total time grows roughly with `MAX_I` squared. Choose `MAX_I` so the
slow scenarios take about a second.