#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "list.h"
Item *CreateItem(T value, Iterator next) {
    Item *i = (Item *)malloc(sizeof(Item));
    i->next = next.node;
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

Iterator InsertAfter(List **l, T value, Iterator iter) {
    if (IsEmpty(l)) {
        (*l)->first = (*l)->last = CreateItem(value, (Iterator){NULL});
        (*l)->first->next = (*l)->first;
        return First(l);
    } else if (IsEqual(iter, Last(l))) {
        (*l)->last->next = CreateItem(value, First(l));
        (*l)->last = (*l)->last->next;
    } else {
        iter.node->next = CreateItem(value, Next(iter));
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
        if (IsEqual(iter, Last(l))) {
            free(iter.node);
            (*l)->first = (*l)->last = NULL;
        } else {
            (*l)->first = iter.node->next;
            (*l)->last->next = (*l)->first;
            free(iter.node);
        }
    } else {
        Iterator prev = First(l);
        while (Next(prev).node != iter.node) {
            prev = Next(prev);
        }
        prev.node->next = iter.node->next;
        if (IsEqual(iter, Last(l))) {
            (*l)->last = prev.node;
        }
        free(iter.node);
    }

    return result;
}

void Destroy(List *l) {
    if (!IsEmpty(&l)) {
        Iterator i = First(&l);
        while (i.node != l->last) {
            Iterator next = Next(i);
            free(i.node);
            i = next;
        }
        free(l->last);
    }
    free(l);
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
        k++;
        if (i.node == (*l)->last) {
            break;
        }
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
            if (i.node && i.node->next && i.node->next->next) {
                Swp(&i.node->value, &i.node->next->next->value);
            }
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
        (*l)->last = Next(Last(l)).node;
    }
}
