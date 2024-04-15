#ifndef __STACK__
#define __STACK__
#include <stdbool.h>
typedef int T;

typedef struct Node {
    T value;
    struct Node *next;
} Node;

typedef struct Stack {
    int size;
    Node *top;
} Stack;

Stack StackInit();
void StackPush(Stack *stk, T value);
T StackPop(Stack *stk);
T StackTop(Stack *stk);
bool StackIsEmpty(Stack *stk);
void StackPrint(Stack *stk);
void StackFree(Stack *stk);
void Swap(Stack* stk, int count);
void StackCopy(Stack* stk, Stack* stk1);
void QuickSort(Stack* stk, int end);
int Sort1(Stack* stk, int end);

#endif