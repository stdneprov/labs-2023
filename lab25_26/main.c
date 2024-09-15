#include <stdio.h>

#include "stack.h"

int main(void) {
    // вариант   3
    // структура 1:  стек
    // операция  5:  слияние двух стеков, деков, списков или очередей,
    // упорядоченных по возрастанию, с сохранением порядка
    printf("a v:\t add element v\n");
    printf("r:\t pop last element\n");
    printf("p: print\n");
    printf("s: sort stack\n");
    printf("q: quit\n");
    printf("> ");
    char c;
    int a;
    stack *s = stack_create();
    while (true) {
        scanf("%c", &c);
        if (c == '\n') {
            continue;
        }
        if (c == 'a') {
            scanf("%d", &a);
            stack_push_back(s, a);
        } else if (c == 'r') {
            stack_pop_back(s);
        } else if (c == 'p') {
            stack_print(s);
        } else if (c == 's') {
            stack_sort(s);
        } else if (c == 'q') {
            return 0;
        } else {
            printf("unknown commad %c\n", c);
        }
        printf("> ");
    }
    stack_free(s);
    return 0;
}
