#ifndef STACK_H
#define STACK_H
#include <stdbool.h>

typedef enum type {
    NUM, SYMB, VAR
} type;

typedef union variable {
    char* symb;
    int num;
} variable;

typedef struct Cell {
    type type;
    variable value;
    struct Cell *next;
} Cell;

typedef struct Stack {
    int len;
    Cell *top;
} Stack;

Stack StackInit();
void StackPush(Stack *stk, int value, type type);
variable StackPop(Stack *stk);
variable StackTop(Stack *stk);
bool StackIsEmpty(Stack *stk);
void StackPrint(Stack *stk);
void StackFree(Stack *stk);

#endif


