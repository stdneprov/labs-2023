#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "list.h"

void ListInit(List *l) {
    l->last = NULL;
    l->size = 0;
}

bool IsEqual(Iterator iter1, Iterator iter2) {
    return iter1.node == iter2.node;
}

bool IsTerminator(Iterator iter) {
    return iter.node == NULL;
}

bool IsEmpty(List *l) {
    return (l)->first == NULL;
}

T GetValue(Iterator iter) {
    return iter.node->data;
}

void SetValue(Iterator iter, T value) {
    iter.node->data = value;
}
Iterator Last(List *l) {
    return (Iterator){(l)->last};
}

Iterator First(List *l)  {
    return (Iterator){(l)->first};
}

Iterator Next(Iterator iter) {
    if (iter.node->next == NULL) {
        
    }
    return (Iterator){iter.node->next};
}

Iterator Previous(Iterator iter) {
    return (Iterator){iter.node->prev};
}

void Add(List *l, T value) {
    if (l->size == 0) {
        l->data[l->size].data = value;
        l->data[l->size].next = NULL;
        l->data[l->size].prev = NULL;
        l->first = &l->data[l->size];
        l->last = &l->data[l->size];
        l->size++;
        return;
    }
    l->data[l->size].data = value;
    l->last->next = &l->data[l->size];
    l->data[l->size].prev = l->last;
    l->last = &l->data[l->size];
    l->last->next = NULL;
    l->size++;
}

Iterator InsertAfter(List *l, T value, Iterator iter) {
    if (l->size == 0) {
        Add(l, value);
    } else if (l->size < POOL_SIZE) {
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

void Destroy(List *l) {
    l->first = 0;
    l->size = 0;
    l->last = 0;
}

void Print(List *l) {
    for (Iterator i = First(l); !IsTerminator(i); i = Next(i)) {
        printf("%d ", GetValue(i));
    }
    printf("\n");
}
