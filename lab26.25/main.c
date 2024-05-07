#include "list.h"
#include <stdio.h>
enum Command { EXIT, PUSH, PUSH_BACK, POP, POP_BACK, PRINT, SORT, DELETE };


void MenuPrint() {
    printf("0 exit\n"
           "1 push by index\n"
           "2 push back\n"
           "3 pop by index\n"
           "4 pop back\n"
           "5 print list\n"
           "6 sort list\n"
           "7 delete list\n\n");
}


int Menu() {
    List *list = List_create();
    while (1) {
        enum Command cmd;
        int value, index = 0;
        MenuPrint();
        scanf("%d", &cmd);
        switch (cmd) {
        case EXIT:
            return 0;
        case PUSH_BACK:
            printf("<value>\n");
            scanf("%d", &value);
            List_push_back(list, value);
            List_print(list);
            break;
        case PUSH:
            printf("<index> <value>\n");
            scanf("%d %d", &index, &value);
            List_insert(list, value, index);
            List_print(list);
            break;
        case PRINT:
            List_print(list);
            break;
        case POP:
            printf("<index>\n");
            scanf("%d", &index);
            List_pop(list, index);
            List_print(list);
            break;
        case POP_BACK:
            List_pop_back(list);
            List_print(list);
            break;
        case SORT:
            List_sort(list);
            List_print(list);
            break;
        case DELETE:
            List_delete(&list);
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
