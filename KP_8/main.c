#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "list.h"
// функция удаления всех элементов кроме заданного числа
void Menu(List *nums) {
    char input[40];
    char addCommand[40] = "add";
    char showCommand[40] = "print";
    char deleteCommand[40] = "delete";
    char exitCommand[40] = "exit";
    char lengthCommand[40] = "count";
    char taskCommand[40] = "task";
    char command[40] = "";
    Iterator iter;
    bool wasCreated = false;

    while(strcmp(command, exitCommand) != 0) {
        printf("------------------------------------------------------------------------------------------------\n");
        printf("$ add value - will add value (instead \"value\" type your number)\n");
        printf("$ print - will show list\n");
        printf("$ task value - will delete all numbers except value (instead \"value\" type your number)\n");
        printf("$ count - show length\n");
        printf("$ delete value - will delete value (instead \"value\" type your number)\n");
        printf("$ exit - stop program\n");
        printf("------------------------------------------------------------------------------------------------\n");

        char command[40] = "";
        fgets(input, sizeof(char) * 20, stdin);
        if (feof(stdin)) {
            Destroy(nums);
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
        //num = strtod(input, NULL, 10);
        sscanf(forNum, "%lf", &num);

        if (strcmp(command, addCommand) == 0) {
            InsertAfter(&nums, num, Last(&nums));
        } else if (strcmp(command, lengthCommand) == 0) {
            printf("%d\n", Count(&nums));
        } else if (strcmp(command, showCommand) == 0) {
            Print(&nums);
        } else if (strcmp(command, deleteCommand) == 0) {
            DeleteNum(nums, num);
        } else if (strcmp(command, taskCommand) == 0) {
            DeleteAllExcept(nums, num);
        } else  if (strcmp(command, exitCommand) == 0) {
            Destroy(nums);
            break;
        } 
        else {
            printf("-Wrong command\n");
        }
    }
}

int main() {
    List *nums;
    ListInit(&nums);
    Menu(nums);
    InsertAfter(&nums, 7.564, Last(&nums));
    InsertAfter(&nums, -909, Last(&nums));
    InsertAfter(&nums, 0, Last(&nums));
    DeleteAllExcept(nums, 0);
    Print(&nums);
}