#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "list.h"

int main() {
    List *lst;
    char input[20];
    char initList[10] = "init";
    char addList[10] = "add";
    char countList[10] = "count";
    char delLastValue[10] = "delLast";
    char delFirstValue[10] = "delFirst";
    char swapValue[15] = "swap";
    char exitMenu[10] = "exit";
    char printList[10] = "print";
    char command[10] = "";

    while(strcmp(command, exitMenu) != 0) {
        printf("\n");
        printf("❤️❤️❤️❤️❤️❤️❤️❤️❤️❤️❤️❤️❤️❤️❤️❤️❤️❤️❤️❤️❤️❤️❤️❤️❤️❤️❤️❤️❤️\n");
        printf("# init  - создать список\n");
        printf("# add value - добавить значение в конец списка\n");
        printf("# delFirst - удалить первый элемент\n");
        printf("# delLast - удалить последний элемент\n");
        printf("# swap k - поменять местами k-1 и k+1 элементы\n");
        printf("# count - показать длину списка\n");
        printf("# print - показать список\n");
        printf("# exit - выйти\n");
        printf("❤️❤️❤️❤️❤️❤️❤️❤️❤️❤️❤️❤️❤️❤️❤️❤️❤️❤️❤️❤️❤️❤️❤️❤️❤️❤️❤️❤️❤️\n");

        char command[15] = "";
        fgets(input, sizeof(char) * 20, stdin);
        if (feof(stdin)) {
            break;
        }
        T num;
        int ind = 0;
        char forNum[20] = "";
        for (int i = 0; input[i] != '\n'; ++i) {
            if (input[i] != ' ' && input[i] !='\n' && input[i] > '9') {
                command[i] = input[i];
                input[i] = ' ';
            }
            else {
                if (input[i] != ' ' && input[i] !='\n') {
                    forNum[ind] = input[i];
                    ind++;
                }
            }
        }
        sscanf(forNum, "%lf", &num);

        if (strcmp(command, initList) == 0) {
            ListInit(&lst);
        } else if (strcmp(command, addList) == 0) {
            InsertAfter(&lst, num, Last(&lst));
        } else if (strcmp(command, delLastValue) == 0) {
            Delete(&lst, Last(&lst));
        } else if (strcmp(command, delFirstValue) == 0) {
            Delete(&lst, First(&lst));
        } else if (strcmp(command, swapValue) == 0) {
            printf("🎶🎶🎶🎶🎶🎶🎶🎶🎶🎶🎶🎶🎶🎶🎶🎶🎶🎶🎶🎶🎶🎶🎶🎶\n");
            if (num == 0) {
                Swap(&lst, Count(&lst) - 1);
            } else {
                Swap(&lst, num - 1);
            }
            Print(&lst);
            printf("🎶🎶🎶🎶🎶🎶🎶🎶🎶🎶🎶🎶🎶🎶🎶🎶🎶🎶🎶🎶🎶🎶🎶🎶\n");
        } else if (strcmp(command, printList) == 0) {
            Print(&lst);
        } else if (strcmp(command, countList) == 0) {
            printf("%d\n", Count(&lst));
        } else if (strcmp(command, exitMenu) == 0) {
            Destroy(lst);
            break;
        } else {
            printf("-Неправильная команда 🤡☠️\n");
        }
    }
}
