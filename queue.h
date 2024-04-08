#ifndef QUEUE_H
#define QUEUE_H
#include <stdbool.h>

typedef int T;

typedef struct Node {
    struct Node *next;
    struct Node *prev;
    T value;
} Node;

typedef struct Queue {
    Node *head;
    Node *tail;
} Queue;

Queue QueueInit();
bool QueuePush(Queue *q, T value);
T QueuePop(Queue *q);
T QueueGetLast(Queue *q);
bool QueueIsEmpty(Queue *q);
void QueuePrint(Queue *q);
void QueueFree(Queue *q);
T GetLenght(Queue *q);
void InsertionSort(Queue *q);

#endif