#ifndef _RINGLIST_H_
#define _RINGLIST_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


typedef struct RingList List;
typedef struct DataType DataType;
typedef struct Complex Complex;
typedef DataType* ListAllocator;

struct RingList {
    ListAllocator lalloc;
    DataType* begin;

    size_t mem;
    size_t size;
};

struct Complex {
    int real;
    int imaginary;
};

struct DataType {
    Complex value;
    int idx;
    bool inuse;
    DataType* next;
    DataType* prev;
};


Complex ToComplex(const int, const int);
void ComplexPrint(const Complex*);

void ListCreate(List**);
bool ListIsEmpty(const List*);
size_t ListSize(const List*);

void ListInsert(List*, const int, const Complex);
void ListPushBack(List*, const Complex);
void ListRemove(List*, const int);

void ListExtend(List*, const size_t, const Complex);

void ListPrint(const List*);
void ListSysPrint(const List*);
void ListClear(List*);
void ListDelete(List**);

#endif