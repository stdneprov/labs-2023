#ifndef _LIST_H_
#define _LIST_H_

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct List List;
typedef struct ListNode ListNode;
struct List {
    ListNode *head;
};

struct ListNode {
    int value;
    ListNode *next;
    ListNode *prev;
};

List *ListCreate();
bool ListIsEmpty(const List *list);
ListNode *ListNodeCreate(int value);
ListNode *GetNodeByIndex(List *list, int index);
void ListInsert(ListNode *prev, int value);
void ListInsertByIndex(List *list, int value, int index);
ListNode *GetLastNode(const List *list);
void ListPushBack(List *list, int value);
void ListPrint(const List *list);
void ListPop(ListNode *node);
void ListPopByIndex(List *list, int index);
void ListPopBack(List *list);
void ListSort(List *list);
void NodesClear(ListNode *node);
void ListClear(List *list);
void ListDelete(List **list);
#endif
