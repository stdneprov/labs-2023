#include "stack.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

void Hello() {
    printf("Это меню управления программой\n");
    printf("Если хочешь добавить значение - введи push и в следующей строке значение\n");
    printf("Если хочешь посмотреть stack - введи print\n");
    printf("Если хочешь удалить значение - введи pop\n");
    printf("Если хочешь получить результат сортировки - введи sort\n");
    printf("Если хочешь выйти - введи exit или ctrl+D\n");
    printf("В случае неверной команды ничего не произойдет\n");
}


void Menu() {
    Hello();
    char inputUser[10] = "";
    Stack stk = StackInit();
    

    while(!feof(stdin)) {
        char inputUser[10] = "";
        fgets(inputUser, sizeof(char) * 10, stdin);
        fflush(stdin);

        if (strcmp(inputUser, "print\n") == 0){
            StackPrint(&stk);
            printf(">\n");
            continue;
        } else if (strcmp(inputUser, "push\n") == 0) {
            int a;
            printf("Введите значение элемента: ");
            scanf("%d", &a);
            StackPush(&stk, a);
            printf("\n>\n");
            continue;
        } else if (strcmp(inputUser, "sort\n") == 0) {
            QuickSort(&stk, stk.size);
            StackPrint(&stk);
            printf("\n>\n");
            continue;
        } else if ((strcmp(inputUser, "pop\n") == 0)) {
            printf("Элемент %d удалён", StackPop(&stk));
            printf("\n>\n");
            continue;
        } else if ((strcmp(inputUser, "exit\n") == 0)) {
            break;
        }
        printf("\n>\n");
    }

}

int main() {
    Menu();
    return 0;

}