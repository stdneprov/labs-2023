#ifndef Stack_h
#define Stack_h
#include <stdio.h>
#include <stdlib.h>

// Структура элемента стека
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// Структура стека
typedef struct {
    Node* top;
} Stack;

void Init(Stack* stack);

int IsEmpty(Stack* stack);

void Push(Stack* stack, int data);

int Pop(Stack* stack);
int StackTop(Stack* stack);
void StackPrint(Stack *stk);
void BubbleSort(Stack *stack);
void StackFree(Stack *stack);

#endif