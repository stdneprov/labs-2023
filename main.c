#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "list.h"

void Sort(List **list) {
    List* l = *list;
    List* buf = ListInit();
    for (Iterator i = First(l); !IsTerminator(l, i); i = Next(&i)) {
        InsertSort(buf, i.node->data);
    }
    *list = buf;
    Destroy(l);
}

int main () {
    char command = ' ';
    int ind;
    int arg;
    List* list[5] = {NULL, NULL, NULL, NULL, NULL};
    printf("i - init\n"); //создать
    printf("a - add\n"); //добавить
    printf("d - destroy\n"); //разрушить/удалить 
    printf("n - insert\n"); //вставка элемента 
    printf("s - sort\n"); //сортировка
    printf("q - quit\n"); //выход 

    while (command != 'q') {
        scanf("%c", &command);
        switch (command) {
        case 'i': {
            scanf("%d", &ind);
            list[ind] = ListInit();
            break;
        }
        case 'a': {
            scanf("%d %d", &ind, &arg);
            Add(list[ind], arg);
            Print(list[ind]);
            break;
        }
        case 'q': {
            for (int i = 0; i < 5; i++) {
                if (list[i] != NULL) {
                    Destroy(list[i]);
                    list[i] = NULL; 
                } 
            }
            break;
        }
        case 'd': {
            scanf("%d", &ind);
            Destroy(list[ind]);
            list[ind] = NULL;
            break;
        }
        case 'n': {
            scanf("%d %d", &ind, &arg);
            InsertSort(list[ind], arg);
            Print(list[ind]);
            break;
        }
        case 's': {
            scanf("%d", &ind);
            Sort(&(list[ind]));
            Print(list[ind]);
            break;
        }
        }
    }
    return 0;
}

