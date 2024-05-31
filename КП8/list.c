#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "list.h"

Item *CreateItem(T value, Iterator prev, Iterator next) {
    Item *i = (Item *)malloc(sizeof(Item));
    i->next = next.node;
    i->prev = prev.node;
    i->value = value;
    return i;
}

void ListInit(List **l) {
    *l = (List *)malloc(sizeof(List));
    (*l)->first = (*l)->last = NULL;
}

Iterator Last(List **l) {
    return (Iterator){(*l)->last};
}

Iterator First(List **l)  {
    return (Iterator){(*l)->first};
}

Iterator Next(Iterator iter)  {
    return (Iterator){iter.node->next};
}

Iterator Previous(Iterator iter)  {
    return (Iterator){iter.node->prev};
}

Iterator Insert(List **l, T value, Iterator iter) {

    if (IsEmpty(l)) {
        (*l)->first = (*l)->last = CreateItem(value, First(l), Last(l));
        return First(l);
    } else if (IsEqual(iter, Last(l))) {
        (*l)->last = CreateItem(value, Last(l), Next(Last(l)));
        (*l)->last->prev->next = (*l)->last;
        (*l)->last->next = (*l)->first;
        (*l)->first->prev = (*l)->last;
    } else {
        iter.node->next = CreateItem(value, iter, Next(iter));
        iter.node->next->next->prev = iter.node->next;
    }

    return Next(iter);

}


bool IsEqual(Iterator iter1, Iterator iter2) {
    return iter1.node == iter2.node;
}

bool IsTerminator(Iterator iter) {
    return iter.node == NULL;
}

bool IsEmpty(List **l) {
    return (*l)->first == NULL;
}

T Delete(List **l, Iterator iter) {
    if (IsEmpty(l) || IsTerminator(iter)) {
        return -1;
    } 

    T result = GetValue(iter);

    if (IsEqual(iter, First(l))) {
        (*l)->first = Next(iter).node;
        (*l)->first->prev = Last(l).node;
        (*l)->last->next = (*l)->first;
    } else if (IsEqual(iter, Last(l))) {
        (*l)->last = Previous(iter).node;;
        (*l)->last->next = First(l).node;
        (*l)->first->prev = (*l)->last;
    }  else {
        iter.node->next->prev = iter.node->prev;
        iter.node->prev->next = iter.node->next;
    }
    free(iter.node);
    return result;
}

void Destroy(List *l) {
    for (Iterator i = First(&l); !IsTerminator(i); i = Next(i)) {
        if (i.node->next == (l)->first){
            free(i.node);
            break;
        }
        free(i.node);
    }
    l->first = l->last = NULL;
}

T GetValue(Iterator iter) {
    return iter.node->value;
}

void SetValue(Iterator iter, T value) {
    iter.node->value = value;
}

void Swp(T *a, T *b) {
    T c = *a;
    *a = *b;
    *b = c;
}

int Count(List **l) {
    int k = 0;
    if (IsEmpty(l)) {
        return 0;
    }
    for (Iterator i = First(l); !IsTerminator(i); i = Next(i)) {
        if (i.node->next == (*l)->first){
            k++;
            break;
        }
        k++;
    }
    return k;
}

void Swap(List **l, int k) {
    if (!IsEmpty(l)) {
        if (Count(l) >= 3) {
            Iterator i = First(l);
            int j = 0;
            while (j != k) {
                i = Next(i);
                j++;
            }
            Swp(&Previous(i).node->value, &Next(i).node->value);
        }
    }
}

void Print(List **l) {
    for (Iterator i = First(l); !IsTerminator(i); i = Next(i)) {
        if (i.node->next == (*l)->first){
            printf("%lf ", GetValue(i));
            break;
        }
        printf("%lf ", GetValue(i));
    }
    printf("\n");
}

void ShiftForward(List **l) {
    if (!IsEmpty(l) && Count(l) > 1) {
        (*l)->first = (*l)->last;
        (*l)->last = Previous(Last(l)).node;
    }
}
