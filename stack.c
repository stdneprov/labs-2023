#include <stdio.h>
#include "stack.h"
#include "tree.h"

Stack* InitStack() {
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    if (stack == NULL) {
//        printf("Ошибка инициализаци, недостаточно памяти\n");
        return NULL;
    }
    
    stack->bottom = malloc(11 * sizeof(Elem));
    if (stack->bottom == NULL) {
//        printf("Ошибка инициализаци, недостаточно памяти\n");
        return NULL;
    }
    stack->top = stack->bottom;
    stack->size = 0;
    stack->mem = 10;

//    printf("Стек инициализирован\n");

    return stack;
}

int Push(Stack* stack, Elem elem) {
    stack->top->val = elem.val;
    stack->top->type = elem.type;
    stack->top->priority = elem.priority;
    ++(stack->size);
    ++(stack->top);
    if (stack->size == stack->mem) {
        Elem* old = stack->bottom;
        stack->bottom = (Elem*)realloc(stack->bottom, (((stack->mem)*2 + 1) * sizeof(Elem)));
        if (stack->bottom == NULL) {
//            printf("Элемент не добавлен, недостаточно памяти\n");
            stack->bottom = old;
            return 0;
        }

        stack->top = &((stack->bottom)[stack->size]);
        (stack->mem) *= 2;
    }
//    printf("Элемент добавлен\n");
    return 1;
}

int Empty(Stack* stack) {
    return (stack->size == 0);
}

Elem Top(Stack* stack) {
    return (stack->top)[-1];
}

int Pop(Stack* stack) {

    if (Empty(stack)) {
//        printf("Стек пуст\n");
        return 0;
    }

    --(stack->size);
    --(stack->top);

    if (stack->size == (stack->mem)/4 && stack->mem > 10) {
        Elem* old = stack->bottom;

        stack->bottom = (Elem*)realloc(stack->bottom, ((stack->mem) / 2 + 1)*sizeof(Elem));
        if (stack->bottom == NULL) {
//            printf("Не удалось выделить память\n");
            stack->bottom = old;
            return 0;
        }

        stack->top = &((stack->bottom)[stack->size]);
        stack->mem /= 2;
    }

//    printf("Элемент удалён\n");
    return 1;
}

void ClearStack(Stack* stack) {

    Elem* old = stack->bottom;
    stack->bottom = (Elem*)realloc(stack->bottom, (11 * sizeof(Elem)));
    if (stack->bottom == NULL) {
//        printf("Не получилось очистить стек\n");
        stack->bottom = old;
        return;
    }

    stack->top = stack->bottom;
    stack->size = 0;
    stack->mem = 10;
}

void DeleteStack(Stack** stack) {

    free((*stack)->bottom);
    free(*stack);
    *stack = NULL;
}
