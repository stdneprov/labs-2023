#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "queue.h"

void Create(Queue *q) {
    q->first = q->last = malloc(sizeof(Node));
    q->size = 0;
}

bool QueueIsEmpty(Queue *q) {
    return q->first == q->last;
}

void QueuePush(Queue* queue, int data) {
    Node* newNode = (Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;

    if (queue->last == NULL) {
        queue->first = newNode;
        queue->last = newNode;
        queue->size++;
    } else {
        queue->last->next = newNode;
        queue->last = newNode;
        queue->size++;
    }
}

int QueuePop(Queue* queue) {
    if (QueueIsEmpty(queue)) {
        printf("Queue is empty (Вам вернётся результат -1)\n");
        return -1;
    } else {
        int number = queue->first->next->data;
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
    Node* temp = queue->first;
    temp = temp->next;
    while (temp != NULL) {
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

