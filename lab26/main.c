#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "queue.h"

void Hello() {
    printf("Это меню управления программой\n");
    printf("Если хочешь создать очередь - введи create\n");
    printf("Если хочешь добавить значение - введи push и в следующей строке значение\n");
    printf("Если хочешь посмотреть дерево - введи print\n");
    printf("Если хочешь удалить значение - введи pop\n");
    printf("Если хочешь посмотреть длину - введи size\n");
    printf("Если хочешь получить результат моего задания - введи do\n");
    printf("Если хочешь выйти - введи exit или ctrl+D\n");
    printf("В случае неверной команды ничего не произойдет\n");
}


void Menu() {
    Hello();
    char inputUser[10] = "";
    Queue qt;
    Queue *q = &qt;
    

    while(!feof(stdin)) {
        char inputUser[10] = "";
        fgets(inputUser, sizeof(char) * 10, stdin);
        fflush(stdin);
        if (strcmp(inputUser, "create\n") == 0) {
            Create(q);
            printf(">\n");
        } else if (strcmp(inputUser, "print\n") == 0){
            QueuePrint(q);
            printf(">\n");
            continue;
        } else if (strcmp(inputUser, "push\n") == 0) {
            int a;
            printf("Введите значение элемента: ");
            scanf("%d", &a);
            QueuePush(q, a);
            printf(">\n");
            continue;
        } else if (strcmp(inputUser, "size\n") == 0) {
            QueueSize(q);
            printf(">\n");
            continue;
        } else if (strcmp(inputUser, "do\n") == 0) {
            Find(q);
            QueuePrint(q);
            printf(">\n");
            continue;
        } else if ((strcmp(inputUser, "pop\n") == 0)) {
            printf("Элемент %d удалён", QueuePop(q));
            printf(">\n");
            continue;
        } else if ((strcmp(inputUser, "exit\n") == 0)) {
            break;
        }
    }

}

int main() {
    Menu();
    return 0;

}