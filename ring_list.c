#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "ring_list.h"

Complex ToComplex(const int real, const int imaginary) {
    Complex complex;
    complex.real = real;
    complex.imaginary = imaginary;
    return complex;
}

void ComplexPrint(const Complex* complex) {
    if (complex->imaginary < 0) {
        printf ("(%d - %di)", complex->real, -complex->imaginary);
    } else {
        printf ("(%d + %di)", complex->real, complex->imaginary);
    }
}

void ListCreate(List** list) {
    *list = (List*)malloc(sizeof(List));
    if (*list == NULL) {
        return;
    }
    
    (*list)->lalloc = malloc(11 * sizeof(Complex));
    if ((*list)->lalloc == NULL) {
        return;
    }

    (*list)->begin = (ListIterator*)malloc(sizeof(ListIterator));
    (*list)->begin->list = *list;
    (*list)->begin->shift = 0; 
    (*list)->size = 0;
    (*list)->mem = 10;
}

bool ListIsEmpty(const List* list) {
    return (list->size == 0);
}

size_t ListSize(const List* list) {
    return list->size;
}

ListIterator ListBegin(List* list) {
    return(*(list->begin));
}

ListIterator ListEnd(List* list) {
    ListIterator end;
    end.list = list;
    end.shift = (list->begin->shift + list->size) % list->mem;
    return(end);
}

ListIterator IteratorNext(const ListIterator iter) {
    ListIterator next = iter;
    
    next.shift = (iter.list->begin->shift + ((iter.list->size + (iter.shift - iter.list->begin->shift + 1) 
                    % iter.list->size) % iter.list->size)) % iter.list->mem;   
    return next;
}

ListIterator IteratorPrev(const ListIterator iter) {
    ListIterator prev = iter;
    
    prev.shift = (iter.list->begin->shift + ((iter.list->size + (iter.shift - iter.list->begin->shift - 1) 
                    % iter.list->size) % iter.list->size)) % iter.list->mem;
    return prev;
}

ListIterator IteratorGet(const List* list, const int idx) {
    ListIterator iter = *(list->begin);
    iter.shift = (iter.shift + ((iter.list->size + idx % iter.list->size) % iter.list->size)) % iter.list->mem;
    return iter;
}

Complex* IteratorUnpack(const ListIterator iter) {
    return &(iter.list->lalloc[iter.shift]);
}

void ListInsert(List* list, const int idx, const Complex value) {
    
    ++(list->size);

    if (list->size == list->mem) {
        list->lalloc = (ListAllocator)realloc(list->lalloc, (((list->mem)*2 + 1) * sizeof(Complex)));
        
        for (int i = 0; i < list->begin->shift - 1; ++i) {
            list->lalloc[list->size + i] = list->lalloc[i];
        }

        (list->mem) *= 2;
    }

    ListIterator cursor = IteratorGet(list, idx);
    
    Complex buff;
    Complex to_write = value;

    do {
        buff = *IteratorUnpack(cursor);
        *IteratorUnpack(cursor) = to_write;
        to_write = buff;
        cursor = IteratorNext(cursor);
    } while (IteratorUnpack(cursor) != IteratorUnpack(*(list->begin)));
}

void ListPushBack(List* list, const Complex value) {
    ListIterator cursor = ListEnd(list);

    ++(list->size);

    if (list->size == list->mem) {
        list->lalloc = (ListAllocator)realloc(list->lalloc, (((list->mem)*2 + 1) * sizeof(Complex)));
        
        for (int i = 0; i < list->begin->shift - 1; ++i) {
            list->lalloc[list->size + i] = list->lalloc[i];
        }

        (list->mem) *= 2;
    }
    
    *IteratorUnpack(cursor) = value;
}

void ListRemove(List* list, const int idx) {

    ListIterator cur = IteratorGet(list, idx);
    if (IteratorUnpack(cur) == IteratorUnpack(*(list->begin))){
        list->begin->shift = (list->begin->shift + 1) % list->mem;
    } else {
        ListIterator next = IteratorNext(cur);
        while (IteratorUnpack(next) != IteratorUnpack(*(list->begin))) {
            *IteratorUnpack(cur) = *IteratorUnpack(next);
            cur = IteratorNext(cur);
            next = IteratorNext(next);
        }
    }

    --(list->size);

    if (list->size == (list->mem)/4 && list->mem > 10) {
        for (size_t i = 0; i < list->size; ++i) {
            list->lalloc[i] = list->lalloc[list->begin->shift + i];
        }
        list->begin->shift = 0;
        
        list->lalloc = (ListAllocator)realloc(list->lalloc, ((list->mem) / 2 + 1)*sizeof(Complex));
        
        list->mem /= 2;
    }
}

Complex ListGet(const List* list, const int idx) {
    return *(IteratorUnpack(IteratorGet(list, idx)));
}

void ListExtend(List* list, const size_t size, const Complex value) {
    while (list->size < size) {
        ListPushBack(list, value);
    }
}

void ListPrint(const List* list) {
    if (ListIsEmpty(list)) {
        return;
    }
    ListIterator iter = *(list->begin);
    do {
        ComplexPrint(IteratorUnpack(iter));
        putchar(' ');
        iter = IteratorNext(iter);
    } while (IteratorUnpack(iter) != IteratorUnpack(*(list->begin)));
    putchar('\n');
}

void ListSysPrint(const List* list) {
    for (size_t i = 0; i < list->mem; ++i) {
        if ((list->begin->shift + list->size) % list->mem >= list->begin->shift) {

            if ((i >= (list->begin->shift + list->size) % list->mem || i < list->begin->shift)) {
                printf(". ");
            } else {
                printf("* ");
            }
        } else {
            if ((i >= (list->begin->shift + list->size) % list->mem && i < list->begin->shift)) {
                printf(". ");
            } else {
                printf("* ");
            }
        }
    }
    putchar('\n');
}

void ListClear(List* list) {

    list->lalloc = (ListAllocator)realloc(list->lalloc, (11 * sizeof(Complex)));
    list->begin->shift = 0;

    list->size = 0;
    list->mem = 10;
}

void ListDelete(List** list) {
    if (*list != NULL) {
        free((*list)->lalloc);
        free((*list)->begin);
        free(*list);
        *list = NULL;
    }
}
