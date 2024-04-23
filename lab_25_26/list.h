#ifndef __LIST__
#define __LIST__
#define POOL_SIZE 100
#include <stdbool.h>

typedef int T;

typedef struct Item {
    T data;
    struct Item *prev;
    struct Item *next;
} Item;

typedef struct Iterator {
    Item *node;
} Iterator;

typedef struct List {
    Item* last;
    int size;
    Item* first;
    Item data[POOL_SIZE + 1];
} List;


void ListInit(List *l);
bool IsEqual(Iterator iter1, Iterator iter2); 
bool IsTerminator(Iterator iter);
bool IsEmpty(List *l);
T GetValue(Iterator iter);
void SetValue(Iterator iter, T value);
Iterator Last(List *l);
Iterator First(List *l);
Iterator Next(Iterator iter);
Iterator Previous(Iterator iter);
void Add(List *l, T value);
Iterator InsertAfter(List *l, T value, Iterator iter);
Iterator InsertBefore(List *l, T value, Iterator iter);
void Destroy(List *l);
void Print(List *l);
#endif