#ifndef INC_24LAB_STACK_H
#define INC_24LAB_STACK_H
#include <stdio.h>
#include <stdlib.h>  // malloc
typedef struct Stack Stack;
typedef struct Node Node;
typedef struct Token Token;
typedef union ValueStackNode ValueStackNode;
Stack *InitStack();
Node *StackTop(Stack *stack);
void AddIntToStack(Stack *stack, int value);
void AddCharToStack(Stack *stack, char value, int sign);
void PrintStack(Stack *stack);
enum TypeStackNode { OPERATOR, NUM, VAR };
Node StackPop(Stack *stack);

union ValueStackNode {
    char letter;
    int num;
};

struct Node {
    ValueStackNode val;
    enum TypeStackNode type;
    int priority;
    Node *next;
    int sign;
};

struct Stack {
    Node *top;
    int size;
};
struct Token {
    enum TypeStackNode type;
    ValueStackNode val;
    int sign;
};
#endif
