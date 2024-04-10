// реализовать стек
// мердж сорт
#include <string.h>
#include <stdio.h>
#include "stack.h"
#include "sort.h"
#include <stdbool.h>
#include <stdlib.h>


int main() {
    Stack stk;
    char input[20];
    char initStack[10] = "init";
    char pushStack[10] = "push";
    char freeStack[10] = "free";
    char sortStack[15] = "sort";
    char exitMenu[10] = "exit";
    char printStack[10] = "print";
    char command[10] = "";

    while(strcmp(command, exitMenu) != 0) {
        printf("\n");
        printf("====================================================================\n");
        printf("# init  - create stack\n");
        printf("# push value - add value in tree\n");
        printf("# free - delet stack\n");
        printf("# sort - sorting stack\n");
        printf("# exit - stop programm\n");
        printf("# print - print stack\n");
        printf("====================================================================\n");

        char command[15] = "";
        fgets(input, sizeof(char) * 20, stdin);
        if (feof(stdin)) {
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
        
        if (strcmp(command, initStack) == 0) {
            stk = StackInit();
        } else if (strcmp(command, pushStack) == 0) {
            StackPush(&stk, num);
        } else if (strcmp(command, freeStack) == 0) {
            StackFree(&stk);
        } else if (strcmp(command, printStack) == 0) {
            StackPrint(&stk);
        } else if (strcmp(command, sortStack) == 0) {
            StackSort(&stk);
        } else if (strcmp(command, exitMenu) == 0) {
            break;
        } else {
            printf("-Wrong command\n");
        }
    }
    
}