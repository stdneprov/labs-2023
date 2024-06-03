#ifndef __QUEUE__
#define __QUEUE__
#include <stdbool.h>

typedef struct Node {
    int data;
    struct Node* next;
}Node;

typedef struct Queue {
    int size;
    struct Node* first;
    struct Node* last;
}Queue;


void Create(Queue *q);
void QueuePush(Queue *q, int value);
int QueuePop(Queue *q);
bool QueueIsEmpty(Queue *q);
void QueuePrint(Queue *q);
void QueueSize(Queue *q);
void Find(Queue *q);
void QueueFree(Queue *q);

#endif