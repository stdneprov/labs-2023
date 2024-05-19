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

ListNode *ListNodeCreate(int value) {
    ListNode *node = (ListNode *)malloc(sizeof(ListNode));
    (node)->value = value;
    (node)->next = NULL;
    (node)->prev = NULL;
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

void ListInsert(Iterator prev, int value) {
    if (prev.node == NULL) {
        return;
    }
    ListNode *node = ListNodeCreate(value);
    ListNode *next;
    next = prev.node->next;
    prev.node->next = node;
    node->prev = prev.node;
    node->next = next;
    if (next != NULL) {
        next->prev = node;
    }
}

void ListInsertByIndex(List *list, int value, int index) {
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
void ListPushBack(List *list, int value) {
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

void ListPop(Iterator node) {
    if (node.node->prev != NULL) {
        node.node->prev->next = node.node->next;
    }
    if (node.node->next != NULL) {
        node.node->next->prev = node.node->prev;
    }
    free(node.node);
}
void ListPopByIndex(List *list, int index) {
    if (index == 0) {
        ListNode *node = list->head;
        list->head = list->head->next;
        free(node);
        return;
    }
    Iterator node = GetNodeByIndex(list, index);
    ListPop(node);
}

void ListPopBack(List *list) {
    Iterator node = GetLastNode(list);
    ListPop(node);
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

Iterator *Prev(Iterator *it) {
    it->node = it->node->prev;
    return it;
}

int Fetch(Iterator it) { return it.node->value;}

void Store(Iterator it, int value) { it.node->value = value; }