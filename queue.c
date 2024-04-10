#include <stdlib.h>
#include <stdio.h>
#include "queue.h"

udt udt_create() {
    udt new;
    new.head = new.tail = NULL;
    return new;
}

bool udt_push(udt *q, T value) {
    QueueItem *new = (QueueItem *)malloc(sizeof(QueueItem));
    if (new == NULL) {
        return false;
    }

    new->value = value;
    new->next = q->head;
    new->previous = NULL;
    if (q->head != NULL) {
        q->head->previous = new;
    }
    q->head = new;
    if (q->tail == NULL) {
        q->tail = new;
    }
    return true;
}

T udt_pop(udt *q) {
    if (udt_is_empty(q)) {
        return -1;
    }

    T value = q->tail->value;

    if (q->head == q->tail) {
        free(q->tail);
        q->head = q->tail = NULL;
    } else {
        QueueItem *buff = q->tail;
        q->tail = q->tail->previous;
        q->tail->next = NULL;
        free(buff);
    }

    return value;
}

T udt_size(udt *q) {
    int length = 0;
    for (QueueItem *i = q->head; i != NULL; i = i->next) {
        length++;
    }
    return length;
}

T udt_last(udt *q) {
    if (udt_is_empty(q)) {
        return -1;
    }
    return q->tail->value;
}

bool udt_is_empty(udt *q) {
    return q->head == NULL && q->tail == NULL;
}

void udt_print(udt *q) {
    for (QueueItem *i = q->head; i != NULL; i = i->next) {
        printf("%d", i->value);
        if (i->next != NULL) {
            printf(" -> ");
        }
    }
    printf("\n");
}

void udt_free(udt *q) {
    QueueItem *next;
    for (QueueItem *i = q->head; i != NULL; i = next) {
        next = i->next;
        free(i);
    }
    q->head = q->tail = NULL;
}
