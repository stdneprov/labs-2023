#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "list.h"

List* ListInit() {  //создаем список
    List* list = (List*)malloc(sizeof(List));
    for (int i = 0; i < POOL_SIZE; i++) {
        list->data[i].next = &(list->data[i+1]);
    }
    list->data[POOL_SIZE - 1].next = NULL;
    list->last = &(list->data[POOL_SIZE]);
    list->last->prev = list->last->next = list->last;
    list->first = &(list->data[0]);
    list->size = 0;
}

Iterator Next(Iterator* iter) {
    iter->node = iter->node->next;
    return *iter;
}

Iterator Previous(Iterator* iter) {
    iter->node = iter->node->prev;
    return *iter;
}

T GetValue(Iterator iter) {
    return iter.node->data;
}

void SetValue(Iterator iter, T value) {
    iter.node->data = value;
}
void Add(List *l, T value) {
    l->first->data = value;

    l->last->prev->next = l->first;
    l->first->prev = l->last->prev;

    l->last->prev = l->first;
    Item* buf = l->first->next;
    l->first->next = l->last;
    l->first = buf;
    l->size++;
}
Iterator Last(List *l) {
    return (Iterator){(l)->last};
}

Iterator First(List *l)  {
    return (Iterator){(l)->last->next};
}

bool IsEmpty(List *l) {
    return IsEqual((First(l)), (Last(l)));
}


bool IsEqual(Iterator iter1, Iterator iter2) {
    return iter1.node == iter2.node;
}

bool IsTerminator(List *l, Iterator iter) {
    return IsEqual(iter, Last(l));
}

// -------------------------------------------------------------------------------------------------------

Iterator InsertAfter(List *l, T value, Iterator iter) {
    if (l->size == 0) {
        Add(l, value);
    } else if (l->size < POOL_SIZE) {
        l->first = l->first->next;
        l->data[l->size].data = value;
        l->data[l->size].next = iter.node->next;
        if (iter.node->next != NULL) {
            iter.node->next->prev = &(l->data[l->size]);
        } else {
            l->last = &(l->data[l->size]);
            l->last->next = NULL;
        }
        l->data[l->size].prev = iter.node;
        iter.node->next = &(l->data[l->size]);
        l->size++;
    } else {
        printf("ЛИСТ ПЕРЕПОЛНЕН\n");
    }

}

Iterator InsertBefore(List *l, T value, Iterator iter) {
    if (l->size == 0) {
        Add(l, value);
    } else if (l->size < POOL_SIZE) {
        l->first = l->first->next;
        l->data[l->size].data = value;
        l->data[l->size].next = iter.node;
        if (iter.node->prev != NULL) {
            iter.node->prev->next = &(l->data[l->size]);
        } 
        if (IsEqual(iter, First(l))) {
            l->first = &(l->data[l->size]);
            l->first->prev = NULL;
        }
        l->data[l->size].prev = iter.node->prev;
        iter.node->prev = &(l->data[l->size]);
        l->size++;
    } else {
        printf("ЛИСТ ПЕРЕПОЛНЕН\n");
    }

}

void InsertSort(List* l, T value) {
    int flag = 0;
    for (Iterator i = First(l); !IsTerminator(l, i); i = Next(&i)) {
        if (i.node->data > value) {
            InsertAfter(l, value, Previous(&i));
            flag = 1;
            break;
        } 
    } 

    if (flag == 0) {
        Add(l, value);
    } 
}

void Destroy(List *l) {
    free (l);
}

void Print(List *l) {
    printf("-- ");
    for (Iterator i = First(l); !IsTerminator(l, i); i = Next(&i)) {
        printf("%d ", GetValue(i));
    }
    printf("\n");
}