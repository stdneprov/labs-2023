#include "deq.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

void Hello() {
    printf("Это меню управления программой\n");
    printf("Если хочешь добавить левое значение - введи pushl и в следующей строке значение\n");
    printf("Если хочешь добавить правое значение - введи pushr и в следующей строке значение\n");
    printf("Если хочешь посмотреть дерево - введи print\n");
    printf("Если хочешь удалить левое значение - введи popl\n");
    printf("Если хочешь удалить правое значение - введи popr\n");
    printf("Если хочешь получить результат сортировки - введи do\n");
    printf("Если хочешь выйти - введи exit или ctrl+D\n");
    printf("В случае неверной команды ничего не произойдет\n");
}


void Menu() {
    Hello();
    char inputUser[10] = "";
    Deq d = DeqInit();
    

    while(!feof(stdin)) {
        char inputUser[10] = "";
        fgets(inputUser, sizeof(char) * 10, stdin);
        fflush(stdin);

        if (strcmp(inputUser, "print\n") == 0){
            DeqPrint(&d);
            printf(">\n");
            continue;
        } else if (strcmp(inputUser, "pushl\n") == 0) {
            int a;
            printf("Введите значение элемента: ");
            scanf("%d", &a);
            DeqPushFront(&d, a);
            printf("\n>\n");
            continue;
        } else if (strcmp(inputUser, "pushr\n") == 0) {
            int a;
            printf("Введите значение элемента: ");
            scanf("%d", &a);
            DeqPushBack(&d, a);
            printf("\n>\n");
            continue;
        } else if (strcmp(inputUser, "sort\n") == 0) {
            QuickSort(&d, d.size);
            DeqPrint(&d);
            printf("\n>\n");
            continue;
        } else if ((strcmp(inputUser, "popr\n") == 0)) {
            printf("Элемент %d удалён", DeqPopBack(&d));
            printf("\n>\n");
            continue;
        } else if ((strcmp(inputUser, "popl\n") == 0)) {
            printf("Элемент %d удалён", DeqPopFront(&d));
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