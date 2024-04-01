#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

#define LEN 10

Stack* InitStack() {
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    stack->array = (T*)malloc(sizeof(T) * LEN);
    stack->maxLen = LEN;
    stack->index = -1;
    return stack;
}

int IsEmpty(Stack* stack) {
    if (stack == NULL) {
        return 1;
    }
    if (stack->index == -1) {
        return 1;
    } else {
        return 0;
    }
}

void Push(Stack* stack, T value) {
    if (stack == NULL) {
        return;
    }
    stack->index++;
    if (stack->index >= stack->maxLen) {
        stack->array = realloc(stack->array, sizeof(T) * stack->maxLen * 2);
        stack->maxLen = stack->maxLen * 2;
    }
    (stack->array)[stack->index] = value;
}

T Pop(Stack* stack) {
    if (IsEmpty(stack)) {
        printf("Ohhhh");
        return 0;
    }
    stack->index--;
    return (stack->array)[stack->index + 1];
}

T LookLast(Stack* stack) {
    if (!IsEmpty(stack)) {
        return (stack->array)[stack->index];
    }
    return 0;
}

int Size(Stack* stack) {
    if (stack == NULL) {
        return 0;
    }
    return stack->index + 1;
}

void DelStack(Stack** stack) {
    if (*stack == NULL) {
        return;
    }
    free((*stack)->array);
    free(*stack);
    *stack = NULL;
}

void Reverse(Stack** stack) {
    if (*stack == NULL) {
        return;
    }
    Stack* buf = InitStack();
    while (!IsEmpty(*stack)) {
        Push(buf, Pop(*stack));
    }
    DelStack(stack);
    *stack = buf;
}

void Concatenation(Stack** stack1, Stack** stack2) {
    if ((*stack1 == NULL) || (*stack2 == NULL)) {
        return;
    }
    int len = (*stack1)->maxLen;
    while ((*stack1)->index + (*stack2)->index > len) {
        len = len * 2;
    }
    (*stack1) = realloc((*stack1), sizeof(T) * len);
    Reverse(stack2);
    while (!IsEmpty(*stack2)) {
        Push((*stack1), Pop(*stack2));
    }
    DelStack(stack2);
}

void PrintStack(Stack* stack) {
    if (stack == NULL) {
        return;
    }
    printf("start\n");
    if (stack->index == -1) {
        printf("empty\n");
    } else {
        for(int i = stack->index; i != -1; i--) {
            printf("%d\n", (stack->array)[i]);
        }
    }
    printf("end\n");
}