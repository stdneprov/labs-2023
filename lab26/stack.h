#ifndef __STACK__
#define __STACK__
#include <stdbool.h>

typedef int T;
#define GROWTH 100


typedef struct Stack {
    T *buff;
    int size;
    int count; 
} Stack;

Stack StackInit();
bool StackPush(Stack *stk, T value);
T StackPop(Stack *stk);
T StackTop(Stack *stk);
bool StackIsEmpty(Stack *stk);
void StackPrint(Stack *stk);
void StackFree(Stack *stk);
T StackGetElement(Stack *stk, long long int i);

#endif
