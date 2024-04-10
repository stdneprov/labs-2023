#ifndef QUEUE_H
#define QUEUE_H

#include <stdbool.h>

typedef int T;

typedef struct QueueItem {
    struct QueueItem *next;
    struct QueueItem *previous;
    T value;
} QueueItem;

typedef struct udt {
    QueueItem *head;
    QueueItem *tail;
} udt;

udt udt_create();
T udt_pop(udt *q);
T udt_size(udt *q);
T udt_last(udt *q);
bool udt_push(udt *q, T value);
bool udt_is_empty(udt *q);
void udt_print(udt *q);
void udt_free(udt *q);

#endif
