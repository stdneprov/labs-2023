#ifndef _STACK
#define _STACK
#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

typedef struct Stack Stack;
typedef struct Elem Elem;

struct Elem {
    Value val;
    enum Type type;

    int priority;
};

struct Stack {
    Elem* bottom;
    Elem* top;

    unsigned long int mem;
    unsigned long int size;
};

Stack* InitStack();
int Push(Stack* stack, Elem elem);
int Empty(Stack* stack);
Elem Top(Stack* stack);
int Pop(Stack* stack);
void ClearStack(Stack* stack);
void DeleteStack(Stack** stack);

#endif