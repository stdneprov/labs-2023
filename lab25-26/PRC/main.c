#include "lab26.h"

int main() {
    Stack stack;
    Init(&stack);

    int choice, value;

    while (1) {
        printf("\nВыберите операцию:\n");
        printf("1. Добавить элемент в стек\n");
        printf("2. Удалить элемент из стека\n");
        printf("3. Получить верхний элемент стека\n");
        printf("4. Вывести содержимое стека\n");
        printf("5. Выход\n");
        printf("6. Сортировка линейным выбором, с последующим удалением максимального элемента\n");
        printf("Введите ваш выбор: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Введите значение для добавления: ");
                scanf("%d", &value);
                Push(&stack, value);
                break;
            case 2:
                printf("Извлеченный элемент: %d\n", Pop(&stack));
                break;
            case 3:
                if (StackTop(&stack) == 0){
                    printf("Ошибка: стек пуст");
                }
                else{
                    printf("Верхний элемент стека: %d\n", StackTop(&stack));
                }
                break;
            case 4:
                StackPrint(&stack);
                break;
            case 5:
                printf("Выход из программы.\n");
                exit(0);
            case 6:
                BubbleSort(&stack);
                StackPrint(&stack);
                break;
            default:
                printf("Неверный выбор. Попробуйте снова.\n");
                exit(0);
        }
    }

    StackFree(&stack);

    return 0;
}
