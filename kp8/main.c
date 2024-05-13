// тип элемента - вещественный
// кольцевой двунаправленный список
// обменять местами (k − 1) -й и (k + 1) -й элементы списка (k задается в качестве параметра)
#include "list.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>



int main() {
    List *lst;
    char input[20];
    char initList[10] = "init";
    char addAList[10] = "addA";
    char addBList[10] = "addB";
    char countList[10] = "count";
    char delLastValue[10] = "delLast";
    char delFirstValue[10] = "delFirst";
    char swapValue[15] = "swap";
    char exitMenu[10] = "exit";
    char printList[10] = "print";
    char command[10] = "";

    while(strcmp(command, exitMenu) != 0) {
        printf("\n");
        printf("====================================================================\n");
        printf("# init  - create list\n");
        printf("# addA value - add value after last in list\n");
        printf("# addB value - add value before first in list\n");
        printf("# delFirst - delet first node\n");
        printf("# delLast - delet last node\n");
        printf("# swap k - swap k-1 and k+1value\n");
        printf("# exit - stop programm\n");
        printf("# count - show length list\n");
        printf("# print - print list\n");
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
        } else if (strcmp(command, addAList) == 0) {
            InsertAfter(&lst, num, Last(&lst));
        } else if (strcmp(command, addBList) == 0) {
            InsertBefore(&lst, num, First(&lst));
        } else if (strcmp(command, delLastValue) == 0) {
            Delete(&lst, Last(&lst));
        }  else if (strcmp(command, delFirstValue) == 0) {
            Delete(&lst, First(&lst));
        } else if (strcmp(command, printList) == 0) {
            Print(&lst);
        } else if (strcmp(command, swapValue) == 0) {
            Swap(&lst, num);
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