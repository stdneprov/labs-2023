#include "stack.h"
#include <stdio.h>

int main() {
    size_t idx = 0;
    stack* stacks[10];
    for (size_t i = 0; i < 10; ++i) {
        stacks[i] = NULL;
    }
    printf("Меню:\n1:Создать стэк\n2:Вывести стэк\n3:Добавить элемент в стэк\n4:Извлечь элемент из стэка\n5:Сортировка\n6:Слияние\n");
    int answer;
    scanf("%d", &answer);
    while (answer != 0) {
        switch (answer) {
            case 1: {
                stacks[idx++] = stack_create(0);
                printf("Стэк был создан!\n");
                break;
            }
            case 2: {
                printf("Введите индекс стэка: ");
                size_t j = 0;
                scanf("%ld", &j);
                stack_print(stacks[j]);
                break;
            }
            case 3: {
                printf("Введите индекс стэка: ");
                size_t j = 0;
                scanf("%ld", &j);
                printf("Введите значение, которое нужно добавить: ");
                int value;
                scanf("%d", &value);
                stack_push(stacks[j], value);
                break;
            }
            case 4: {
                printf("Введите индекс стэка: ");
                size_t j = 0;
                scanf("%ld", &j);
                if (!stack_is_empty(stacks[j])) {
                    stack_pop(stacks[j]);
                }
                break;
            }
            case 5: {
                printf("Введите индекс стэка: ");
                size_t j = 0;
                scanf("%ld", &j);
                stack_sort(stacks[j]);
                break;
            }
            case 6: {
                printf("Введите индекс стэка 1: ");
                size_t j1 = 0;
                scanf("%ld", &j1);
                printf("Введите индекс стэка 2: ");
                size_t j2 = 0;
                scanf("%ld", &j2);
                stack* tmp = stack_create(0);
                stack_merge(stacks[j1], stacks[j2], tmp);
                stack_print(tmp);
                stack_free(tmp);
                break;
            }
        }

        printf("Меню:\n1:Создать стэк\n2:Вывести стэк\n3:Добавить элемент в стэк\n4:Извлечь элемент из стэка\n5:Сортировка\n6:Слияние\n");
        scanf("%d", &answer);
    }

    for (size_t i = 0; i < 10; ++i) {
        if (stacks[i]) {
            stack_free(stacks[i]);
        }
    }

    return 0;
}