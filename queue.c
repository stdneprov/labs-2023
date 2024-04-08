#include "queue.h"
#include <stdlib.h>
#include <stdio.h>

Queue QueueInit() {
    Queue new;
    new.head = new.tail = NULL;
    return new;
}

bool QueuePush(Queue *q, T value) {
    Node *new = (Node *)malloc(sizeof(Node));
    if (new == NULL) {
        return false;
    }

    new->value = value;
    new->next = q->head;
    new->prev = NULL;
    if (q->head != NULL) {
        q->head->prev = new;
    }
    q->head = new;
    if (q->tail == NULL) {
        q->tail = new;
    }
    return true;
}

T QueuePop(Queue *q) {
    if (QueueIsEmpty(q)) {
        return -1;
    }

    T value = q->tail->value;

    if (q->head == q->tail) {
        free(q->tail);
        q->head = q->tail = NULL;
    } else {
        Node *buf = q->tail;
        q->tail = q->tail->prev;
        q->tail->next = NULL;
        free(buf);
    }

    return value;
}

T QueueGetLast(Queue *q) {
    if (QueueIsEmpty(q)) {
        return -1;
    }

    T value = q->tail->value;
    return value;
}

bool QueueIsEmpty(Queue *q) {
    return q->head == NULL && q->tail == NULL;
}

void QueuePrint(Queue *q) {
    for (Node *i = q->head; i != NULL; i = i->next) {
        printf("%d", i->value);
        if (i->next != NULL) {
            printf(" -> ");
        }
    }
    printf("\n");
}

void QueueFree(Queue *q) {
    Node *next;
    for (Node *i = q->head; i != NULL; i = next) {
        next = i->next;
        free(i);
    }
}

T GetLenght(Queue *q) {
    int lenght = 0;
    for (Node *i = q->head; i != NULL; i = i->next) {
        lenght += 1;
    }

    return lenght;
}

void InsertionSort(Queue *q) {
    Queue buff = QueueInit();
    while (!QueueIsEmpty(q)) {
        if (!QueueIsEmpty(&buff)) {
            int val1 = QueuePop(q), val2 = QueueGetLast(&buff);
            if ((val2 > val1) && (GetLenght(&buff) == 1)) {
                QueuePush(&buff, val1);
            } else if (val2 > val1) {
                QueuePush(&buff, QueuePop(&buff));
                for (int i = 1; i < GetLenght(&buff); i++) {
                    val2 = QueuePop(&buff);
                    if (val1 > val2) {
                        QueuePush(q, val2);
                    } else {
                        QueuePush(&buff, val2);
                    }
                }
                
                QueuePush(&buff, val1);
            } else {
                while (!QueueIsEmpty(&buff)) {
                    QueuePush(q, QueuePop(&buff));
                }
                QueuePush(&buff, val1);
            }
        } else {
            QueuePush(&buff, QueuePop(q));
        }
    }

    while (!QueueIsEmpty(&buff)) {
        QueuePush(q, QueuePop(&buff));
    }
}