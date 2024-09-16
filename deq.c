#include "deq.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

Deq DeqInit() {
    Deq new;
    new.size = 0;
    new.head = new.tail = NULL;
    return new;
}

bool DeqPushFront(Deq *deq, T value) {
    Node *new = (Node *)malloc(sizeof(Node));
    if (new == NULL) {
        return false;
    }

    new->value = value;
    new->next = deq->head;
    new->prev = NULL;
    //printf("ok");
    //printf("OK");
    if (!(DeqIsEmpty(deq))) {
        deq->head->prev = new;
    }
    deq->head = new;
    deq->size++;
    if (deq->tail == NULL) {
        deq->tail = new;
    }
    return true;
}

bool DeqPushBack(Deq *deq, T value) {
    Node *new = (Node *)malloc(sizeof(Node));
    if (new == NULL) {
        return false;
    }

    new->value = value;
    new->prev = deq->tail;
    new->next = NULL;
    if (!(DeqIsEmpty(deq))) {
        deq->tail->next = new;
    }
    deq->tail = new;
    deq->size++;
    if (deq->head == NULL) {
        deq->head = new;
    }
    return true;
}

T DeqPopBack(Deq *deq) {
    if (DeqIsEmpty(deq)) {
        //printf("NULL");
        return -1;
    }

    T value = deq->tail->value;

    if (deq->head == deq->tail) {
        free(deq->tail);
        deq->head = deq->tail = NULL;
    } else {
        Node *buf = deq->tail;
        deq->tail = deq->tail->prev;
        deq->tail->next = NULL;
        free(buf);
    } // 52 25 22 67 69 228 420 1337 665 806
    deq->size--;
    return value;
}

T DeqPopFront(Deq *deq) {
    if (DeqIsEmpty(deq)) {
        return -1;
    }

    T value = deq->head->value;

    if (deq->head == deq->tail) {
        free(deq->tail);
        deq->head = deq->tail = NULL;
    } else {
        Node *buf = deq->head;
        deq->head = deq->head->next;
        deq->head->prev = NULL;
        free(buf);
    }
    deq->size--;
    return value;
}

T DeqLast(Deq *deq) {
    if (DeqIsEmpty(deq)) {
        return -1;
    }

    T value = deq->tail->value;
    return value;
}

T DeqFirst(Deq *deq) {
    if (DeqIsEmpty(deq)) {
        return -1;
    }

    T value = deq->head->value;
    return value;
}

bool DeqIsEmpty(Deq *deq) {
    return deq->head == NULL && deq->tail == NULL;
}

void DeqPrint(Deq *deq) {
    for (Node *i = deq->head; i != NULL; i = i->next) {
        printf("%d", i->value);
        if (i->next != NULL) {
            printf(" -> ");
        }
    }
}

void DeqFree(Deq *deq) {
    Node *next;
    for (Node *i = deq->head; i != NULL; i = next) {
        next = i->next;
        free(i);
    }
}