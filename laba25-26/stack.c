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

T Pop(Stack* stack) {
    if (IsEmpty(stack)) {
        printf("Error");
        return 0;
    }
    stack->index--;
    return (stack->array)[stack->index + 1];
}

T ExtractMax(Stack* sourceStack, Stack* tempStack) {
    if (IsEmpty(sourceStack)) {
        printf("Error");
        return 0;
    }
    
    T maxItem = Pop(sourceStack);

    while (!IsEmpty(sourceStack)) {
        T item = Pop(sourceStack);
        if (item > maxItem) {
            Push(tempStack, maxItem);
            maxItem = item;
        } else {
            Push(tempStack, item);
        }
    }

    return maxItem;
}
