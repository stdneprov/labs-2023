#include "list.h"
#include <stdio.h>
enum Command { EXIT, PUSH, PUSH_BACK, POP, POP_BACK, PRINT, SHIFT, SIZE, DELETE };


void MenuPrint() {
    printf("0 exit\n"
           "1 insert by index\n"
           "2 insert to end\n"
           "3 pop by index\n"
           "4 pop tail\n"
           "5 print list\n"
           "6 cyclic shift\n"
           "7 get size\n"
           "8 delete list\n\n");
}


int Menu() {
    List *list = ListCreate();
    while (1) {
        enum Command cmd;
        int index = 0;
        unsigned int value = 0;
        MenuPrint();
        scanf("%d", (int*)&cmd);
        switch (cmd) {
        case EXIT:
            return 0;
        case PUSH_BACK:
            printf("<value>\n");
            scanf("%u", &value);
            ListPushBack(list, value);
            ListPrint(list);
            break;
        case PUSH:
            printf("<index> <value>\n");
            scanf("%d %u", &index, &value);
            ListInsertByIndex(list, value, index);
            ListPrint(list);
            break;
        case PRINT:
            ListPrint(list);
            break;
        case POP:
            printf("<index>\n");
            scanf("%d", &index);
            ListPopByIndex(list, index);
            ListPrint(list);
            break;
        case POP_BACK:
            ListPopBack(list);
            ListPrint(list);
            break;
        case SHIFT:
            CyclicShift(list);
            ListPrint(list);
            break;
        case SIZE:
            printf("List size: %d\n", ListSize(list));
            break;
        case DELETE:
            ListDelete(list);
            ListPrint(list);
            break;
        default:
            break;
        }
        printf("\n");
    }
}


int main() {
    Menu();
    return 0;
}