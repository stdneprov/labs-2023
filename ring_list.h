#ifndef _RINGLIST_H_
#define _RINGLIST_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


typedef struct RingList List;
typedef struct Complex Complex;
typedef struct ListIterator ListIterator;
typedef Complex* ListAllocator;

struct RingList {
    ListAllocator lalloc;

    ListIterator* begin;

    size_t mem;
    size_t size;
};

struct Complex {
    int real;
    int imaginary;
};

struct ListIterator {
    List* list;
    int shift;
};


Complex ToComplex(const int, const int);
void ComplexPrint(const Complex*);

void ListCreate(List**);
bool ListIsEmpty(const List*);
size_t ListSize(const List*);

ListIterator ListBegin(List*);
ListIterator ListEnd(List*);
ListIterator IteratorNext(const ListIterator);
ListIterator IteratorPrev(const ListIterator);
ListIterator IteratorGet(const List*, const int);
Complex* IteratorUnpack(const ListIterator);

void ListInsert(List*, const int, const Complex);
void ListPushBack(List*, const Complex);
void ListRemove(List*, const int);
Complex ListGet(const List*, const int);

void ListExtend(List*, const size_t, const Complex);

void ListPrint(const List*);
void ListSysPrint(const List*);
void ListClear(List*);
void ListDelete(List**);

#endif