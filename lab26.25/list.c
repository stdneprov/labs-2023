#include "list.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

List *List_create() {
    List *list = (List *)malloc(sizeof(List));
    (list)->data = (int *)malloc(sizeof(int) * 5);
    if ((list)->data == NULL) {
        return NULL;
    }
    (list)->size = 0;
    (list)->memory = 6;
    (list)->end = (list)->data;
    return list;
}

bool List_is_empty(const List *list) { return ((list->size) == 0); }

void List_insert(List *list, int value, int index) {
    if ((list->size) == (list->memory)) {
        int *old = list->data;
        list->data =
            (int *)realloc(list->data, sizeof(int) * (list->memory * 2 + 1));
        if (list->data == NULL) {
            list->data = old;
            return;
        }
        list->end = &((list->data)[list->size]);
        list->memory *= 2;
    }
    list->size++;
    list->end++;
    int buff = value;
    int prev = value;
    for (int i = index; i < list->size; i++) {
        buff = list->data[i];
        list->data[i] = prev;
        prev = buff;
    }
}

void List_push_back(List *list, int value) {
    List_insert(list, value, list->size);
}

void List_print(const List *list) {
    for (int *i = list->data; i < list->end; i++) {
        printf("%d ", *i);
    }
    printf("\n");
}

void List_pop(List *list, int index) {
    int prev, buff;
    for (int i = list->size - 1; i >= index; i--) {
        buff = list->data[i];
        if (i == list->size - 1) {
            prev = buff;
            continue;
        }
        list->data[i] = prev;
        prev = buff;
    }
    list->size--;
    list->end--;
}

void List_pop_back(List *list) { List_pop(list, list->size - 1); }

void List_sort(List *list) {
    bool flag = true;
    while (flag) {
        flag = false;
        for (int i = 0; i < list->size - 1; i++) {
            if (list->data[i] > list->data[i + 1]) {
                int buff = list->data[i];
                list->data[i] = list->data[i + 1];
                list->data[i + 1] = buff;
                flag = true;
            }
        }
    }
}

void List_clear(List *list) {
    free(list->data);
    list->data = NULL;
}

void List_delete(List **list) {
    List_clear(*list);
    free(*list);
    *list = NULL;
}
