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

#define MIN_CAPACITY 32

typedef struct ANode ANode;
struct ANode {
    size_t node;
    ANode *next;
};

typedef size_t list_type;

typedef struct {
    list_type value;
    size_t next; // 0 - null pointer
    size_t prev; // 0 - null pointer
} ListNode;

typedef struct {
    ListNode *mem;    // where everything is stored
    size_t head;      // index of first element
    size_t size;      // number of elements stored
    size_t capacity;  // current capacity
    ANode *next_free; // pointer to next freed index in memory
} List;

typedef struct {
    List *l;
    size_t node;
} Iterator;

List *LCreate(void);
size_t LLen(const List *l);
bool LIsEmpty(const List *l);
void LPushBack(List *l, list_type v);
void LPushFront(List *l, list_type v);
void LInsert(List *l, size_t i, list_type v);
void LRemove(List *l, size_t i);
void LRemoveInRange(List *l, list_type bottom, list_type top);
void LPrint(List *l);
list_type LGet(List *l, size_t i);
void LSet(List *l, size_t i, list_type v);
void LFree(List *l);

Iterator IFirst(List *l);
Iterator ILast(List *l);
Iterator IAtPos(List *l, size_t i);
Iterator *INext(Iterator *it);
Iterator *IPrev(Iterator *it);
Iterator *IInsert(List *l, Iterator *it, list_type v);
Iterator *IRemove(List *l, Iterator *it);
list_type IGet(List *l, Iterator *it);

#endif
