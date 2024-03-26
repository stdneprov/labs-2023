#ifndef LIST_H
#define LIST_H
#include <stdlib.h>
#include <stdbool.h>

typedef struct Listel Listel;


struct Listel {
    int val;
    int pn;
};

typedef struct {
    int pool_size;
    Listel* buf;
    int barrier;
    int first;
    int size;
    int first_empty;
    int last_add;
} barrier_list;

bool ListInit(barrier_list *l);
void ListDestroy(barrier_list *l);
int ListGetSize(barrier_list *l);

typedef struct {
    barrier_list *lst;
    int prev;
    int cur;
} list_iter;

list_iter ListIterBegin(barrier_list *l);
list_iter ListIterEnd(barrier_list *l);
bool ListIterEqual(list_iter it1, list_iter it2);
void ListIterMoveNext(list_iter *it);
void ListIterMoveBack(list_iter *it);
int ListIterGet(list_iter *it);

void ListIterSet(list_iter *it, int val);
bool ListIterInsertBefore(list_iter *it, int val);
void ListIterRemove(list_iter *it);

list_iter ListIterFind(barrier_list *l, int val);

#endif
