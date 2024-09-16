#ifndef __DEQ__
#define __DEQ__
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef int T;

typedef struct Node {
    struct Node *next;
    struct Node *prev;
    T value;
} Node;

typedef struct Deq {
    Node *head;
    Node *tail;
    int size;
} Deq;

Deq DeqInit();
bool DeqPushFront(Deq *deq, T value);
bool DeqPushBack(Deq *deq, T value);
T DeqPopFront(Deq *deq);
T DeqPopBack(Deq *deq);
T DeqLast(Deq *deq);
T DeqFirst(Deq *deq);
bool DeqIsEmpty(Deq *deq);
void DeqPrint(Deq *deq);
void DeqFree(Deq *deq);

void QuickSort(Deq* d, int end);
int Part(Deq* d, int end);
void Swap(Deq* d, int count);

#endif