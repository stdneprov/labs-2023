#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "stack.h"

void PrintT(T a) {
    printf("%d", a);
}

Stack StackInit() {
    Stack stk;
    stk.count = 0;
    stk.size = GROWTH;
    stk.buff = (T *)malloc(sizeof(T) * stk.size);
    return stk;
}

bool StackPush(Stack *stk, T value) {
    if (stk->buff == NULL) {
        stk->buff = (T *)malloc(sizeof(T));
        if (stk->buff == NULL) {
            printf("ERROR: not enough memory");
            exit(EXIT_FAILURE);
        }
        stk->size = 1;
    }
    if (stk->count >= stk->size) {
        stk->size += GROWTH;
        stk->buff = (T *)realloc(stk->buff, sizeof(T) * stk->size);
        if (stk->buff == NULL) {
            return false;
        }
    }

    stk->buff[stk->count++] = value;
    return true;
}

T StackPop(Stack *stk) {
    if (stk->count <= 0) {
        return -1;
    }
    
    T result = stk->buff[--stk->count];

    if (stk->size - stk->count >= GROWTH) {
        stk->size -= GROWTH / 2;
        stk->buff = (T *)realloc(stk->buff, sizeof(T) * stk->size);
    }

    return result;
}

T StackTop(Stack *stk) {
    if (stk->count <= 0) {
        return -1;
    }

    return stk->buff[--stk->count];
}

bool StackIsEmpty(Stack *stk) {
    return stk->count <= 0;
}

void StackPrint(Stack *stk) {
    if (StackIsEmpty(stk)) {
        printf("Stack is empty");
        exit(-1);
    }

    for (int i = stk->count - 1; i >= 0; i--) {
        PrintT(stk->buff[i]);

        if (i > 0) {
            printf(" -> ");
        }
    }

    printf("\n");
}

void StackFree(Stack *stk) {
    if (stk->buff != NULL) {
        free(stk->buff);
    }
}
