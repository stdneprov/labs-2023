#ifndef _LIST_H_
#define _LIST_H_

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct List List;

struct List {
    int *data;
    int *end;

    int memory;
    int size;
};

List *List_create();
bool List_is_empty(const List *list);
void List_insert(List *list, int value, int index);
void List_push_back(List *list, int value);
void List_pop_back(List *list);
void List_pop(List *list, int index);
void List_print(const List *);

void List_clear(List *);
void List_delete(List **);
void List_sort(List *list);
void List_delete(List **list);
void List_clear(List *list);
#endif