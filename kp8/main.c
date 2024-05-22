#include "list.h"
#include <stdio.h>
enum Command { EXIT, PUSH, PUSH_BACK, POP, POP_BACK, PRINT, SWAP, DELETE };


void MenuPrint() {
    printf("0 exit\n"
           "1 push by index\n"
           "2 push back\n"
           "3 pop by index\n"
           "4 pop back\n"
           "5 print list\n"
           "6 swap list\n"
           "7 delete list\n\n");
}


int Menu() {
    List *list = ListCreate();
    while (1) {
        enum Command cmd;
        int index = 0;
        unsigned int value = 0;
        MenuPrint();
        scanf("%d", &cmd);
        switch (cmd) {
        case EXIT:
            return 0;
        case PUSH_BACK:
            printf("<value>\n");
            scanf("%d", &value);
            ListPushBack(list, value);
            ListPrint(list);
            break;
        case PUSH:
            printf("<index> <value>\n");
            scanf("%d %d", &index, &value);
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
        case SWAP:
            SwapTail(list);
            ListPrint(list);
            break;
        case DELETE:
            ListDelete(&list);
            return 0;
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
