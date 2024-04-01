#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#include "sort.h"
#include "test.h"

void test () {
    char command = ' ';
    int ind;
    int arg;
    Stack* stacks[5] = {NULL, NULL, NULL, NULL, NULL};
    printf("i - init\n");
    printf("u - push\n");
    printf("o - pop\n");
    printf("s - stop\n");
    printf("d - del stack\n");
    printf("r - reverse\n");
    printf("c - concatenation\n");
    printf("q - quick sort\n");
    while (command != 's') {
        scanf("%c", &command);
        switch (command) {
        case 'i': {
            scanf("%d", &ind);
            stacks[ind] = InitStack();
            break;
        }
        case 'u': {
            scanf("%d %d", &ind, &arg);
            Push(stacks[ind], arg);
            PrintStack(stacks[ind]);
            break;
        }
        case 'o': {
            scanf("%d", &ind);
            printf("pop %d\n", Pop(stacks[ind]));
            PrintStack(stacks[ind]);
            break;
        }
        case 's': {
            for (int i = 0; i < 5; i++) {
                if (stacks[i] != NULL) DelStack(&(stacks[i]));
            }
            break;
        }
        case 'r': {
            scanf("%d", &ind);
            Reverse(&(stacks[ind]));
            PrintStack(stacks[ind]);
            break;
        }
        case 'd': {
            scanf("%d", &ind);
            DelStack(&(stacks[ind]));
            break;
        }
        case 'c': {
            scanf("%d %d", &ind, &arg);
            Concatenation(&(stacks[ind]), &(stacks[arg]));
            PrintStack(stacks[ind]);
            break;
        }
        case 'q': {
            scanf("%d", &ind);
            Sort(&(stacks[ind]));
            PrintStack(stacks[ind]);
            break;
        }
        }
    }
    return;
}