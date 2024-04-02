#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

void PushS (Stack* stack, T *value) {
    if (stack->top != NULL) {
        ItemS* newItem = (ItemS*)malloc(sizeof(ItemS));
        newItem->prev = stack->top;
        newItem->value = value;
        stack->top = newItem;
    } else {
        ItemS* newItem = (ItemS*)malloc(sizeof(ItemS));
        newItem->prev = NULL;
        newItem->value = value;
        stack->top = newItem;
    }
}

T *LookLastS (Stack* stack) {
    if (stack->top == NULL) {
        return NULL;
    }
    return stack->top->value;
}

T *PopS (Stack* stack) {
    if (stack->top != NULL) {
        T *value = stack->top->value;
        ItemS *oldTop = stack->top;
        stack->top = stack->top->prev;
        free(oldTop);
        return value;
    } else {
        return NULL;
    }

}