#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "list.h"

void Task(List* nums) {
    int buff;
    for (Iterator j = First(nums); !IsTerminator(Next(j)); j = Next(j)) {
        if (j.node->data > Next(j).node->data) {
            buff = j.node->data;
            SetValue(j, Next(j).node->data);
            SetValue(Next(j), buff);
        }
    }
}

void Menu(List *nums) {
    char input[40];
    char addCommand[40] = "add";
    char insAfterCommand[40] = "insertAfter";
    char insBeforeCommand[40] = "insertBefore";
    char destroyCommand[40] = "destroy";
    char showCommand[40] = "show";
    char showIterCommand[40] = "showIter";
    char deleteCommand[40] = "delete";
    char sortCommand[40] = "sort";
    char taskCommand[40] = "task";
    char nextCommand[40] = "next";
    char prevCommand[40] = "prev";
    char exitCommand[40] = "exit";
    char firstCommand[40] = "first";
    char lastCommand[40] = "last";
    char lengthCommand[40] = "length";
    char command[40] = "";
    Iterator iter;
    bool wasCreated = false;

    while(strcmp(command, exitCommand) != 0) {
        printf("------------------------------------------------------------------------------------------------\n");
        printf("$ add value - will add value (instead \"value\" type your number)\n");
        printf("$ show - will show list\n");
        printf("$ sort - will sort list\n");
        printf("$ task - will change list\n");
        printf("$ next - go to next iterator\n");
        printf("$ prev - go to previous iterator\n");
        printf("$ first - show first value\n");
        printf("$ last - show last value\n");
        printf("$ length - show length\n");
        printf("$ destroy - will destroy list\n");
        printf("$ delete value - will delete value (instead \"value\" type your number)\n");
        printf("$ showIter - will show current iterator\n");
        printf("$ insertAfter value - will add value after current iterator(instead \"value\" type your number)\n");
        printf("$ insertBefore value - will add value before current iterator(instead \"value\" type your number)\n");
        printf("$ exit - stop program\n");
        printf("------------------------------------------------------------------------------------------------\n");

        char command[40] = "";
        fgets(input, sizeof(char) * 20, stdin);
        if (feof(stdin)) {
            Destroy(nums);
            break;
        }
        int num = 0;

        for (int i = 0; input[i] != '\n'; ++i) {
            if (input[i] != ' ' && input[i] !='\n') {
                command[i] = input[i];
                input[i] = ' ';
            }
            else {
                break;
            }
        }
        num = strtol(input, NULL, 10);

        if (strcmp(command, addCommand) == 0) {
            Add(nums, num);
            if (nums->size == 1) {
                wasCreated = true;
                iter = First(nums);
            }
        } else if (strcmp(command, showCommand) == 0) {
            if (wasCreated == true) {
                Print(nums);
            }
        } else if (strcmp(command, destroyCommand) == 0) {
            Destroy(nums);
        } else if (strcmp(command, deleteCommand) == 0) {
            DeleteNum(nums, num);
        } else if (strcmp(command, sortCommand) == 0) {
            int buff;
            for (Iterator i = First(nums); !IsTerminator(i); i = Next(i)) {
                for (Iterator j = First(nums); !IsTerminator(Next(j)); j = Next(j)) {
                    if (j.node->data > Next(j).node->data) {
                        buff = j.node->data;
                        SetValue(j, Next(j).node->data);
                        SetValue(Next(j), buff);
                    }
                }
            }
        } else if (strcmp(command, taskCommand) == 0) {
            Task(nums);
        } else if (strcmp(command, nextCommand) == 0) {
            if (IsEqual(iter, Last(nums)) == false) {
                iter = Next(iter);
            }
            printf("%d\n", GetValue(iter));
        } else if (strcmp(command, prevCommand) == 0) {
            if (IsEqual(iter, First(nums)) == false) {
                iter = Previous(iter);
            }
            printf("%d\n", GetValue(iter));
        } else if (strcmp(command, showIterCommand) == 0) {
            if (wasCreated == true) {
                printf("%d\n", GetValue(iter));
            }
        } else if (strcmp(command, firstCommand) == 0) {
            printf("%d\n", GetValue(First(nums)));
        } else if (strcmp(command, lastCommand) == 0) {
            printf("%d\n", GetValue(Last(nums)));
        } else if (strcmp(command, lengthCommand) == 0) {
            printf("%d\n", nums->size);
        }  else if (strcmp(command, insAfterCommand) == 0) {
            InsertAfter(nums, num, iter);
        } else if (strcmp(command, insBeforeCommand) == 0) {
            InsertBefore(nums, num, iter);
        } else  if (strcmp(command, exitCommand) == 0) {
            Destroy(nums);
            break;
        } 
        else {
            printf("-Wrong command\n");
        }
    }
}

void ReadData(List *nums) {
    char symbol = ' ';
    int valContinue = 0;
    int buff = 0;
    int minus = 1;
    while (symbol != EOF && symbol != '\n') {
        if (symbol != ' ' && symbol != '-') {
            if (valContinue == 1) {
                if (symbol != '0') {
                    buff = Last(nums).node->data;
                    buff = buff * 10 + (symbol - '0') * minus;
                    Last(nums).node->data = buff;
                    valContinue = 1;
                } else {
                    buff = Last(nums).node->data;
                    buff = buff * 10;
                    Last(nums).node->data = buff;
                    valContinue = 1;
                }
            } else {
                Add(nums, (symbol - '0') * minus);
                valContinue = 1;
            }
        } else if (symbol == '-') {
            minus = -1;
        } else {
            valContinue = 0;
            minus = 1;
        }
        symbol = getchar();
    }
}

int main() {
    List nums;
    ListInit(&nums);
    Menu(&nums);
    //ReadData(&nums);
    // int buff;
    // printf("-----------------после преобразования-----------------\n");
    // Task(&nums);
    // Print(&nums);
    // printf("-------------------после сортировки-------------------\n");
    // for (Iterator i = First(&nums); !IsTerminator(i); i = Next(i)) {
    //     for (Iterator j = First(&nums); !IsTerminator(Next(j)); j = Next(j)) {
    //         if (j.node->data > Next(j).node->data) {
    //             buff = j.node->data;
    //             SetValue(j, Next(j).node->data);
    //             SetValue(Next(j), buff);
    //         }
    //     }
    // }
    // Print(&nums);
    
}
