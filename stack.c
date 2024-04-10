#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "stack.h"


void Stack_create(Stack** stack) {
    *stack = (Stack*)malloc(sizeof(Stack));
    if (*stack == NULL) {
        return;
    }
    
    (*stack)->begin = malloc(11 * sizeof(Stack_Item));
    if ((*stack)->begin == NULL) {
        return;
    }
    (*stack)->end = (*stack)->begin;
    (*stack)->size = 0;
    (*stack)->mem = 10;
}

bool Stack_is_empty(const Stack* stack) {

    return (stack->size == 0);
}

void Stack_push(Stack* stack, Stack_Item item) {
    *(stack->end) = item;
    
    ++(stack->size);
    ++(stack->end);

    if (stack->size == stack->mem) {
        Stack_Item* old = stack->begin;
        stack->begin = (Stack_Item*)realloc(stack->begin, (((stack->mem)*2 + 1) * sizeof(Stack_Item)));
        if (stack->begin == NULL) {
            stack->begin = old;
            return;
        }

        stack->end = &((stack->begin)[stack->size]);
        (stack->mem) *= 2;
    }
}

void Stack_pop(Stack* stack) {

    if (Stack_is_empty(stack)) {
        return;
    }

    --(stack->size);
    --(stack->end);

    if (stack->size == (stack->mem)/4 && stack->mem > 10) {
        Stack_Item* old = stack->begin;

        stack->begin = (Stack_Item*)realloc(stack->begin, ((stack->mem) / 2 + 1)*sizeof(Stack_Item));
        if (stack->begin == NULL) {
            stack->begin = old;
            return;
        }

        stack->end = &((stack->begin)[stack->size]);
        stack->mem /= 2;
    }
}

void Stack_print(const Stack* stack) {
    for (Stack_Item* iter = stack->begin; iter < stack->end; ++iter) {
        Stack_Item_print(iter);
    } 
    putchar('\n');
}

size_t Stack_size(const Stack* stack) {
    return stack->size;
}


Stack_Item Stack_top(Stack* stack) {
    return (stack->end)[-1];
}

void Stack_sys_print(const Stack* stack) {
    for (long unsigned int i = 0; i < stack->mem; ++i) {
        if (i < Stack_size(stack)) {
            Stack_Item_print(&(stack->begin[i]));
        } else {
            printf(". ");
        }
    }
    putchar('\n');
}

void Stack_clear(Stack* stack) {

    Stack_Item* old = stack->begin;
    stack->begin = (Stack_Item*)realloc(stack->begin, (11 * sizeof(Stack_Item)));
    if (stack->begin == NULL) {
        stack->begin = old;
        return;
    }

    stack->end = stack->begin;
    stack->size = 0;
    stack->mem = 10;
}

void Stack_delete(Stack** stack) {
    if (*stack != NULL) {
        free((*stack)->begin);
        free(*stack);
        *stack = NULL;
    }
}
