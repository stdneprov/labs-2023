#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "queue.h"

void Create(Queue *q) {
    q->first = q->last = malloc(sizeof(Node));
    q->size = 0;
    //q->first = NULL;
    //q->first = NULL;
}

bool QueueIsEmpty(Queue *q) {
    return q->first == q->last;
}

void QueuePush(Queue* queue, int data) {
    if (!(queue->last->next = malloc(sizeof(Node)))) {
        exit(-1);
    }
    queue->last->data = data;
    queue->last = queue->last->next;
    queue->last->next = NULL;
    //printf("%d !last\n", queue->last->data);
    //printf("%d !first\n", queue->first->data);
    queue->size++;
}

int QueuePop(Queue* queue) {
    if (QueueIsEmpty(queue)) {
        printf("Queue is empty (Вам вернётся результат -1)\n");
        return -1;
    } else {
        int number = queue->first->data;
        queue->size--;
        Node* temp = queue->first;
        queue->first = queue->first->next;
        free(temp);

        if (queue->first == NULL) {
            queue->last = NULL;
        }
        return number;
    }
}

void QueuePrint(Queue* queue) {
    if (QueueIsEmpty(queue)) {
        printf("Выход в связи с ошибкой( Список пуст )");
        exit(-1);
    }
    //printf("%d\n", queue->first->data);
    Node* temp = queue->first;
    //temp = temp->next;
    while (temp->next != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

void QueueSize(Queue* q) {
    printf("%d\n", q->size);
}

void QueueFree(Queue *q) {
    Node *next;
    for (Node *i = q->first; i != NULL; i = next) {
        next = i->next;
        free(i);
    }
}

