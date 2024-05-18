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

ListNode *GetNodeByIndex(List *list, int index) {
    if (ListIsEmpty(list)) {
        return NULL;
    }
    ListNode *prev = list->head;
    for (int i = 0; i < index; i++) {
        if (prev->next == NULL) {
            printf("Index out of bounds\n");
            return NULL;
        }
        prev = prev->next;
    }
    return prev;
}

void ListInsert(ListNode *prev, int value) {
    if (prev == NULL) {
        return;
    }
    ListNode *node = ListNodeCreate(value);
    ListNode *next;
    next = prev->next;
    prev->next = node;
    node->prev = prev;
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
        ListNode *prev;
        prev = GetNodeByIndex(list, index);
        ListInsert(prev, value);
    }
}

ListNode *GetLastNode(const List *list) {
    ListNode *prev = list->head;
    if (prev == NULL) {
        return NULL;
    }
    while (prev->next != NULL) {
        prev = prev->next;
    }
    return prev;
}
void ListPushBack(List *list, int value) {
    ListNode *prev;
    prev = GetLastNode(list);
    if (prev == NULL) {
        list->head = ListNodeCreate(value);

    } else {
        ListInsert(prev, value);
    }
}

void ListPrint(const List *list) {
    ListNode *node = list->head;
    while (node != NULL) {
        printf("%d ", node->value);
        node = node->next;
    }
    printf("\n");
}

void ListPop(ListNode *node) {
    if (node->prev != NULL) {
        node->prev->next = node->next;
    }
    if (node->next != NULL) {
        node->next->prev = node->prev;
    }
    free(node);
}
void ListPopByIndex(List *list, int index) {
    if (index == 0) {
        ListNode *node = list->head;
        list->head = list->head->next;
        free(node);
        return;
    }
    ListNode *node = GetNodeByIndex(list, index);
    ListPop(node);
}

void ListPopBack(List *list) {
    ListNode *node = GetLastNode(list);
    ListPop(node);
}

void ListSort(List *list) {
    bool flag = true;
    ListNode *node;
    while (flag) {
        flag = false;
        node = list->head;
        while (node->next != NULL) {
            if (node->value > node->next->value) {
                int buff = node->value;
                node->value = node->next->value;
                node->next->value = buff;
                flag = true;
            }
            node = node->next;
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
