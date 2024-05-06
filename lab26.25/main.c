#include "list.h"
#include <stdio.h>
enum Command {
    EXIT,
    PUSH,
    PUSH_BACK,
    POP,
    POP_BACK,
    PRINT,
    SORT,
    CLEAR,
    DELETE
};
int main() {
    List* list = List_create();
    while (1) {
        enum Command cmd;
        int value, index = 0;
        scanf("%d", &cmd);
        switch (cmd) {
        case EXIT:
            return 0;
        case PUSH_BACK:
            scanf("%d", &value);
            List_push_back(list, value);
            List_print(list);
            break;
        case PUSH:
            scanf("%d %d", &index, &value);
            List_insert(list, value, index);
            List_print(list);
            break;
        case PRINT:
            List_print(list);
            break;
        case POP:
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
        case CLEAR:
            List_clear(list);
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
    return 0;
}
