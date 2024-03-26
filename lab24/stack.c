#include "stack.h"

#include "base.h"
Stack *InitStack() {
    Stack *stack = (Stack *)malloc(sizeof(Stack));
    if (stack == NULL) {
        return NULL;
    }
    stack->top = NULL;
    stack->size = 0;
    return stack;
}

void AddIntToStack(Stack *stack, int value) {
    Node *node = (Node *)malloc(sizeof(Node));
    if (node == NULL) {
        return;
    }
    stack->size++;
    node->val.num = value;
    node->type = NUM;
    node->priority = -1;
    node->next = stack->top;
    stack->top = node;
}

void AddCharToStack(Stack *stack, char value, int sign) {
    Node *node = (Node *)malloc(sizeof(Node));
    if (node == NULL) {
        return;
    }
    stack->size++;
    if ('a' <= value && value <= 'z') {
        node->type = VAR;
    } else {
        node->type = OPERATOR;
    }
    node->priority = GetPriority(value);
    node->sign = sign;
    node->val.letter = value;
    node->next = stack->top;
    stack->top = node;
}

void PrintStack(Stack *stack) {
    Node *node = stack->top;
    while (node != NULL) {
        if (node->type == NUM) {
            printf("%d ", node->val.num - '0');
        } else {
            printf("%c ", node->val.letter);
        }
        node = node->next;
    }
    printf("\n");
}

Node StackPop(Stack *stack) {
    Node node;
    node.val = stack->top->val;
    node.type = stack->top->type;
    node.priority = stack->top->priority;
    node.sign = stack->top->sign;
    Node *toDel = stack->top;
    stack->top = stack->top->next;
    stack->size--;
    free(toDel);
    return node;
}

Node *StackTop(Stack *stack) { return stack->top; }