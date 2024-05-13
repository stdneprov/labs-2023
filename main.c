#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "ring_list.h"

// 13 % 8 + 1 = 6 - комплексный
// (7 div 2) % 6 + 1 = 4 - кольцевой двунаправленный
// 7 % 15 + 1 = 8 - дополнить список копиями заданного значения до указанной длины k

enum Command {EXIT, PUSH, INSERT, EXTEND, REMOVE, SIZE, PRINT, CLEAR, SYS};

int CommandRead() {
    int cmd;

    printf("\n\
1. Push back item\n\
2. Insert item\n\
3. Extend list to length whith item\n\
4. Remove item\n\
5. Print list size\n\
6. Print list\n\
7. Clear list (delete all the items)\n\
8. Print memory usage\n\
0. Exit\n\
\n");

    scanf("%d", &cmd);
    putchar('\n');
    if (cmd < 0 || cmd > 9) {
        return -1;
    } else {
        return cmd;
    }
}

void CommandExecute(int inp, List** list) {
    enum Command cmd = inp;
    int re, im, idx, k;

    switch (cmd)
    {
        case EXIT:
            ListDelete(list);
            exit(0);
            break;

        case PUSH:
            printf("Enter complex value in format <real> <imaginary>\n");
            scanf("%d %d", &re, &im);
            ListPushBack(*list, ToComplex(re, im));
            break;

        case INSERT:
            printf("Enter complex value in format <real> <imaginary>\n");
            scanf("%d %d", &re, &im);
            printf("\nEnter index\n");
            scanf("%d", &idx);
            ListInsert(*list, idx, ToComplex(re, im));
            break;

        case EXTEND:
            printf("Enter complex value in format <real> <imaginary>\n");
            scanf("%d %d", &re, &im);
            printf("\nEnter length\n");
            scanf("%d", &k);
            ListExtend(*list, k, ToComplex(re, im));
            break;

        case REMOVE:
            printf("Enter index\n");
            scanf("%d", &idx);
            ListRemove(*list, idx);
            break;

        case SIZE:
            printf("List size is %ld\n", ListSize(*list));
            break;
        
        case PRINT:
            ListPrint(*list);
            break;

        case CLEAR:
            ListClear(*list);
            break;

        case SYS:
            ListSysPrint(*list);
            break;
    };
}

int main() {
    List* list;
    ListCreate(&list);
    int cmd;

    while (1) {
        cmd = CommandRead();
        if (cmd != -1) {
            CommandExecute(cmd, &list);
        }
    }

    return 0;
}