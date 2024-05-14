#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
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
    
    (*list)->lalloc = malloc(11 * sizeof(DataType));
    if ((*list)->lalloc == NULL) {
        return;
    }

    (*list)->size = 0;
    (*list)->mem = 10;
    for (size_t i = 0; i < (*list)->mem; i++) {
        (*list)->lalloc[i].inuse = false;
    }
}

bool ListIsEmpty(const List* list) {
    return (list->size == 0);
}

size_t ListSize(const List* list) {
    return list->size;
}

void ListInsert(List* list, const int idx, const Complex value) {
    
    ++(list->size);

    if (list->size == list->mem) {
        list->lalloc = (ListAllocator)realloc(list->lalloc, (((list->mem)*2 + 1) * sizeof(DataType)));
        (list->mem) *= 2;

        for (size_t i = list->size; i < list->mem; ++i) {
            if (i > list->size) {
                list->lalloc[i].inuse = false;
            }
        }
        for (size_t i = 0; i < list->size; ++i) {
            if (list->lalloc[i].idx == 0 && list->lalloc->inuse) {
                list->begin = &(list->lalloc[i]);
                break;
            }
        }
    }

    DataType* next = list->begin;
    if (next != NULL){
        for (int i = 0; i < idx; ++i) {
            next = next->next;
        }
    }
    
    for (size_t i = 0; i < list->size; ++i) {
        if (!list->lalloc[i].inuse) {
            list->lalloc[i].inuse = true;
            list->lalloc[i].value = value;
            list->lalloc[i].idx = i;
            if (next != NULL){
                list->lalloc[i].next = next;
                list->lalloc[i].prev = next->prev;
                list->lalloc[i].next->prev = &(list->lalloc[i]);
                list->lalloc[i].prev->next = &(list->lalloc[i]);
            } else {
                list->lalloc[i].next = &(list->lalloc[i]);
                list->lalloc[i].prev = &(list->lalloc[i]);
                list->begin = &(list->lalloc[i]);
                
            }
            if (list->size > 1 && idx % (list->size - 1) == 0) {
                list->begin = &(list->lalloc[i]);
                
            }
            break;
        }
    }
}

void ListPushBack(List* list, const Complex value) {
    
    ++(list->size);

    if (list->size == list->mem) {
        list->lalloc = (ListAllocator)realloc(list->lalloc, (((list->mem)*2 + 1) * sizeof(DataType)));
        (list->mem) *= 2;

        for (size_t i = list->size; i < list->mem; ++i) {
            if (i > list->size) {
                list->lalloc[i].inuse = false;
            }
        }
        for (size_t i = 0; i < list->size; ++i) {
            if (list->lalloc[i].idx == 0 && list->lalloc->inuse) {
                list->begin = &(list->lalloc[i]);
                break;
            }
        }
    }

    DataType* next = list->begin;
    
    
    for (size_t i = 0; i < list->size; ++i) {
        if (!list->lalloc[i].inuse) {
            list->lalloc[i].inuse = true;
            list->lalloc[i].value = value;
            list->lalloc[i].idx = i;
            if (next != NULL){
                list->lalloc[i].next = next;
                list->lalloc[i].prev = next->prev;
                list->lalloc[i].next->prev = &(list->lalloc[i]);
                list->lalloc[i].prev->next = &(list->lalloc[i]);
            } else {
                list->lalloc[i].next = &(list->lalloc[i]);
                list->lalloc[i].prev = &(list->lalloc[i]);
                list->begin = &(list->lalloc[i]);
                
            }
            
            break;
        }
    }
}


void ListRemove(List* list, const int idx) {
    if (!list->lalloc[idx].inuse) {
        return;
    }

    list->lalloc[idx].inuse = false;
    if (idx % list->size == 0) {
        list->begin = list->lalloc[idx].next;
    }
    list->lalloc[idx].prev->next = list->lalloc[idx].next;
    list->lalloc[idx].next->prev = list->lalloc[idx].prev;

    --(list->size);

    if (list->size == (list->mem)/4 && list->mem > 10) {
        
        list->lalloc = (ListAllocator)realloc(list->lalloc, ((list->mem) / 2 + 1)*sizeof(DataType));
        list->mem /= 2;
    }
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
    DataType* iter = list->begin;
    for (size_t i = 0; i < list->size; ++i) {
        ComplexPrint(&(iter->value));
        putchar(' ');
        iter = iter->next;
    }
    putchar('\n');
}

void ListSysPrint(const List* list) {
    for (size_t i = 0; i < list->mem; ++i) {
        if (list->lalloc[i].inuse) {
            printf("* ");
        } else {
            printf(". ");
        }
    }
    putchar('\n');
}

void ListClear(List* list) {

    list->lalloc = (ListAllocator)realloc(list->lalloc, (11 * sizeof(DataType)));
    list->begin = NULL;
    

    list->size = 0;
    list->mem = 10;
    for (size_t i = 0; i < list->mem; i++) {
        list->lalloc[i].inuse = false;
    }
}

void ListDelete(List** list) {
    if (*list != NULL) {
        free((*list)->lalloc);
        free(*list);
        *list = NULL;
    }
}
