#ifndef _LIST_H_
#define _LIST_H_

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct List List;
typedef struct ListNode ListNode;
typedef struct Iterator Iterator;
struct List {
    ListNode *head;
};

struct ListNode {
    unsigned int value;
    ListNode *next;
};

struct Iterator {
    ListNode *node;
};
List *ListCreate();
ListNode *ListNodeCreate(unsigned int value);
bool ListIsEmpty(const List *list);
ListNode *ListNodeCreate(unsigned int value);
Iterator GetNodeByIndex(List *list, int index);
void ListInsert(Iterator prev, unsigned int value);
void ListInsertByIndex(List *list, unsigned int value, int index);
Iterator GetLastNode(const List *list);
void ListPushBack(List *list, unsigned int value);
void ListPrint(const List *list);
void ListPop(Iterator node);
void ListPopByIndex(List *list, int index);
void ListPopBack(List *list);
void ListSort(List *list);
void NodesClear(ListNode *node);
void ListClear(List *list);
void ListDelete(List **list);
Iterator First(const List *list);
bool Equal(const Iterator *it1, const Iterator *it2);
bool NotEqual(const Iterator *it1, const Iterator *it2);
Iterator* Next(Iterator *it);
Iterator* Prev(Iterator *it);
unsigned int Fetch(Iterator it);
void Store(Iterator it, unsigned int value);
bool IsLast(const Iterator *it);
int ListSize(const List *list);
void SwapTail(List *list);
#endif
