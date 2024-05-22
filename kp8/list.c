#include "list.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

List *ListCreate() {
    List *list = (List *)malloc(sizeof(List));
    (list)->head = NULL;
    return list;
}

bool ListIsEmpty(const List *list) { return ((list->head) == NULL); }

ListNode *ListNodeCreate(unsigned int value) {
    ListNode *node = (ListNode *)malloc(sizeof(ListNode));
    (node)->value = value;
    (node)->next = NULL;
    return node;
}

Iterator GetNodeByIndex(List *list, int index) {
    int buffIndex = index;
    if (ListIsEmpty(list)) {
        exit(1);
    }
    Iterator i;
    for (i = First(list); buffIndex > 0; Next(&i)) {
        buffIndex--;
    }
    return i;
}

void ListInsert(Iterator prev, unsigned int value) {
    if (prev.node == NULL) {
        return;
    }
    ListNode *node = ListNodeCreate(value);
    ListNode *next;
    next = prev.node->next;
    prev.node->next = node;
    node->next = next;
}

void ListInsertByIndex(List *list, unsigned int value, int index) {
    if (index == 0) {
        ListNode *node = ListNodeCreate(value);
        node->next = list->head;
        list->head = node;
    } else {
        Iterator prev;
        prev = GetNodeByIndex(list, index);
        ListInsert(prev, value);
    }
}

Iterator GetLastNode(const List *list) {
    Iterator prev = First(list);
    while (!IsLast(&prev)) {
        Next(&prev);
    }
    return prev;
}
void ListPushBack(List *list, unsigned int value) {
    Iterator prev;
    prev = GetLastNode(list);
    if (prev.node == NULL) {
        list->head = ListNodeCreate(value);
    } else {
        ListInsert(prev, value);
    }
}

void ListPrint(const List *list) {
    Iterator node = First(list);
    while (!IsLast(&node)) {
        printf("%d ", Fetch(node));
        Next(&node);
    }
    printf("%d ", Fetch(node));
    printf("\n");
}

void ListPop(Iterator prev) {
    ListNode *old = prev.node->next;
    prev.node->next = old->next;
    free(old);
}
void ListPopByIndex(List *list, int index) {
    if (index == 0) {
        ListNode *node = list->head;
        list->head = list->head->next;
        free(node);
        return;
    }
    Iterator prev = GetNodeByIndex(list, index - 1);
    ListPop(prev);
}

void ListPopBack(List *list) {
    Iterator prev = GetNodeByIndex(list, ListSize(list) -1);
    ListPop(prev);
}

void ListSort(List *list) {
    bool flag = true;
    Iterator node;
    while (flag) {
        flag = false;
        node = First(list);
        while (!IsLast(&node)) {
            if (Fetch(node) > node.node->next->value) {
                int buff = Fetch(node);
                Store(node, node.node->next->value);
                node.node->next->value = buff;
                flag = true;
            }
            Next(&node);
        }
    }
}

void NodesClear(ListNode *node) {
    if (node->next != NULL) {
        NodesClear(node->next);
    }
    free(node);
}
void ListClear(List *list) {
    NodesClear(list->head);
    free(list);
}

void ListDelete(List **list) {
    ListClear(*list);
    *list = NULL;
}

Iterator First(const List *list) {
    Iterator it;
    it.node = list->head;
    return it;
}

bool Equal(const Iterator *it1, const Iterator *it2) {
    return it1->node == it2->node;
}

bool NotEqual(const Iterator *it1, const Iterator *it2) {
    return !(Equal(it1, it2));
}

bool IsLast(const Iterator *it) {
    if (it->node == NULL) {
        return true;
    }
    return it->node->next == NULL;
}

Iterator *Next(Iterator *it) {
    it->node = it->node->next;
    return it;
}


unsigned int Fetch(Iterator it) { return it.node->value;}

void Store(Iterator it, unsigned int value) { it.node->value = value; }

int ListSize(const List *list) {
    int size = 0;
    Iterator it = First(list);
    while (!IsLast(&it)) {
        size++;
        Next(&it);
    }
    return size + 1;
}

void SwapTail(List *list) {
    Iterator it = GetNodeByIndex(list, ListSize(list) / 2);
    Iterator newLast = GetNodeByIndex(list, ListSize(list) / 2 - 1);
    Iterator last = GetLastNode(list);
    newLast.node->next = NULL;
    last.node->next = list->head;
    list->head = it.node;
}
