#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "stack.h"

Stack StackInit() {
    Stack new;
    new.top = NULL;
    new.size = 0;
    return new;
}

void StackPush(Stack *stk, T value) {
    Node *new = (Node *)malloc(sizeof(Node));
    if (new == NULL) {
        exit(-1);
    }
    new->next = stk->top;
    stk->top = new;
    stk->top->value = value;
    stk->size += 1;
}

T StackPop(Stack *stk) {
    T val = stk->top->value;
    Node *buff = stk->top;
    stk->top = stk->top->next;
    stk->size -= 1;
    free(buff);
    return val;
}

T StackTop(Stack *stk) {
    return stk->top->value;
}

bool StackIsEmpty(Stack *stk) {
    return stk->top == NULL;
}

void StackPrint(Stack *stk) {
    for (Node *i = stk->top; i != NULL; i = i->next) {
        printf("%d", i->value);
        if (i->next != NULL) {
            printf(" -> ");
        }
    }
}

void StackFree(Stack *stk) {
    Node *next;
    for (Node *i = stk->top; i != NULL; i = next) {
        next = i->next;
        free(i);
    }
}