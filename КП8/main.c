#include "list.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int main() {
    List *lst;
    char input[20];
    char initList[10] = "init";
    char addList[10] = "add";
    char countList[10] = "count";
    char delLastValue[10] = "delLast";
    char delFirstValue[10] = "delFirst";
    char shiftForward[15] = "shift";
    char swapValue[15] = "swap";
    char exitMenu[10] = "exit";
    char printList[10] = "print";
    char command[10] = "";

    while(strcmp(command, exitMenu) != 0) {
        printf("\n");
        printf("====================================================================\n");
        printf("# init  - create list\n");
        printf("# add value - add value after last in list\n");
        printf("# delFirst - delet first node\n");
        printf("# delLast - delet last node\n");
        printf("# shift - shift to next");
        printf("# count - show length list\n");
        printf("# print - print list\n");
        printf("# exit - stop programm\n");
        printf("====================================================================\n");

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
        } else if (strcmp(command, shiftForward) == 0) {
            ShiftForward(&lst);
        } else if (strcmp(command, printList) == 0) {
            Print(&lst);
        } else if (strcmp(command, countList) == 0) {
            printf("%d\n", Count(&lst));
        } else if (strcmp(command, exitMenu) == 0) {
            Destroy(lst);
            break;
        } else {
            printf("-Wrong command\n");
        }
    }
}
