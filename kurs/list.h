#ifndef __LIST_H__
#define __LIST_H__

#include <stddef.h>
#include <stdbool.h>

// field type 6 % 8 + 1 = 6 + 1 = 7 = беззнаковое целое
// type (6 / 2) % 6 + 1 = 3 % 6 + 1 = 3 + 1 = 4 = кольцевой двунаправленный
// action = 6 % 15 + 1 = 7 == удалить элементы списка со значениями в данном
// диапазоне
/*

Печать списка.
2. Вставка нового элемента в список.
3. Удаление элемента из списка.
4. Подсчет длины списка.

*/

typedef struct ListNode ListNode;

typedef size_t list_type;

struct ListNode {
    size_t value;
    ListNode *next;
    ListNode *prev;
};

typedef struct {
    ListNode *head;
    size_t len;
} List;

struct List {
    ListNode *head;
    size_t len;
};

typedef struct {
    ListNode *node;
} Iterator;

List *LCreate(void);
size_t LLen(const List *l);
bool LIsEmpty(const List *l);
void LPushBack(List *l, list_type v);
void LPushFront(List *l, list_type v);
void LInsert(List *l, size_t i, list_type v);
void LRemove(List *l, size_t i);
void LRemoveInRange(List *l, list_type bottom, list_type top);
void LPrint(const List *l);
list_type LGet(const List *l, size_t i);
void LSet(List *l, size_t i, list_type v);
void LFree(List *l);

Iterator IFirst(const List *l);
Iterator ILast(const List *l);
Iterator IAtPos(const List *l, size_t i);
Iterator *INext(Iterator *it);
Iterator *IPrev(Iterator *it);
Iterator *IInsert(Iterator *it, list_type v);
Iterator *IRemove(Iterator *it);
list_type IGet(Iterator *it);

#endif
