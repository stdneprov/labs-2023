#include "stack.h"
#include <stdlib.h>
#include <stdio.h>

Stack StackInit() {
    Stack new;
    new.top = NULL;
    return new;
}

void StackPush(Stack *stk, int value, type type) {
    Cell *new = (Cell *)malloc(sizeof(Cell));
    if (new == NULL) {
        exit(-1);
    }
    new->next = stk->top;
    stk->top = new;
    if (type == NUM) {
        stk->top->value.num = value;
        stk->top->type = NUM;
    } else if (type == SYMB) {
        stk->top->value.symb = (char *)malloc(sizeof(char));
        if (stk->top->value.symb == NULL) {
            exit(-1);
        }
        *stk->top->value.symb = value;
        stk->top->type = SYMB;
    } else {
        stk->top->value.symb = (char *)malloc(sizeof(char));
        if (stk->top->value.symb == NULL) {
            exit(-1);
        }
        *stk->top->value.symb = value;
        stk->top->type = VAR;
    }
    stk->len += 1;
}

variable StackPop(Stack *stk) {
    variable val = stk->top->value;
    Cell *buff = stk->top;
    stk->top = stk->top->next;
    stk->len -= 1;
    free(buff);
    return val;
}

variable StackTop(Stack *stk) {
    return stk->top->value;
}

bool StackIsEmpty(Stack *stk) {
    return stk->top == NULL;
}

void StackPrint(Stack *stk) {
    for (Cell *i = stk->top; i != NULL; i = i->next) {
        if (i->type == SYMB) {
            printf("%c ", *i->value.symb);
        } else if (i->type == VAR) {
            printf("%s ", i->value.symb);
        } else {
            printf("%d ", i->value.num);
        }
    }
}

void StackFree(Stack *stk) {
    Cell *next;
    for (Cell *i = stk->top; i != NULL; i = next) {
        next = i->next;
        free(i);
    }
}
