#ifndef __LIST_H__
#define __LIST_H__

#include <stdlib.h>

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
    ListNode *tail;
} List;

struct List {
    ListNode *head;
    ListNode *tail;
};

typedef struct {
    ListNode *node;
} Iterator;

#endif
