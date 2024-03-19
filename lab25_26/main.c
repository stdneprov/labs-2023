#include <stdio.h>

#include "stack.h"

int main(void) {
    // вариант   3
    // структура 1:  стек
    // операция  5:  слияние двух стеков, деков, списков или очередей,
    // упорядоченных по возрастанию, с сохранением порядка
    stack *a = stack_create();
    stack *b = stack_create();
    stack *c = stack_create();
    for (int i = 10; i >= 0; i--) {
        stack_push_back(a, i * 2);
        stack_push_back(b, i * 2 + 1);
    }
    printf("unsorted:\n");
    stack_print(a);
    stack_print(b);
    stack_sort(a);
    stack_sort(b);
    stack_merge(c, a, b);
    printf("sorted:\n");
    stack_print(a);
    stack_print(b);
    printf("merged:\n");
    stack_print(c);
    return 0;
}
