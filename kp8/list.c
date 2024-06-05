#include <stdio.h>
#include <stdlib.h>
#include "list.h"

Node* CreateNode(float data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("malloc error\n");
        return NULL;
    }
    newNode->data = data;
    newNode->next = newNode;
    return newNode;
}

List CreateList() {
    List list;
    list.head = NULL;
    return list;
}

Iterator Start(List* list) {
    Iterator iter;
    iter.node = list->head;
    iter.list = list;
    return iter;
}

Iterator Next(Iterator iter) {
    if (iter.node == NULL) {
        printf("iterator error\n");
        return iter;
    }
    iter.node = iter.node->next;
    return iter;
}

void InsertAfter(Iterator* iter, float data) {
    Node* newNode = CreateNode(data);
    if (newNode == NULL) {
        return;
    }
    if (iter->node == NULL) {  // пустой список
        newNode->next = newNode;  // указывает сам на себя
        iter->node = newNode;
        iter->list->head = newNode;
    } else {
        newNode->next = iter->node->next;
        iter->node->next = newNode;
    }
}

void Push(Iterator* iter, float data) {
    Node* newNode = CreateNode(data);
    if (newNode == NULL) {
        return;
    }
    if (iter->list->head == NULL) {
        newNode->next = newNode;
        iter->node = newNode;
        iter->list->head = newNode;
    } else {
        Node* current = iter->list->head;
        while (current->next != iter->list->head) {
            current = current->next;
        }
        newNode->next = iter->list->head;  // некст на начало списка
        current->next = newNode;  // в конец списка
        iter->list->head = newNode; 
    }
}

void DeleteNode(Iterator* iter, float value) {
    if (iter->list->head == NULL) { 
        printf("list is empty\n");
        return;
    }
    Node* current = iter->list->head;
    Node* prev = NULL;
    do {
        if (current->data == value) {
            if (prev == NULL) { 
                if (current->next == current) {  // единственный элемент
                    free(current);
                    iter->node = NULL;
                    iter->list->head = NULL;
                } else {
                    Node* tail = current;
                    while (tail->next != current) {
                        tail = tail->next;
                    }
                    iter->list->head = current->next;
                    tail->next = iter->list->head;
                    free(current);
                    iter->node = iter->list->head;
                }
            } else {
                prev->next = current->next;
                if (current == iter->list->head) { 
                    iter->list->head = current->next;
                }
                free(current);
                iter->node = iter->list->head;
            }
            return;
        }
        prev = current;
        current = current->next;
    } while (current != iter->list->head);
    printf("value not found\n");
}

void FreeList(List* list) {
    if (list->head == NULL) {
        return;
    }
    Node* current = list->head;
    do {
        Node* next = current->next;
        free(current);
        current = next;
    } while (current != list->head);
    list->head = NULL;
}

int ListLength(List* list) {
    if (list->head == NULL) {
        printf("list is empty\n");
        return 0;
    }
    int length = 0;
    Node* current = list->head;
    do {
        length++;
        current = current->next;
    } while (current != list->head);
    return length;
}

void ClearListIfExists(List* list, float value) {
    if (list->head == NULL) {
        return;
    }
    Node* current = list->head;
    do {
        if (current->data == value) {
            FreeList(list);
            printf("value found. the list is cleared\n");
            return;
        }
        current = current->next;
    } while (current != list->head);
    printf("value not found\n");
}

void PrintList(List* list) {
    if (list->head == NULL) {
        printf("list is empty\n");
        return;
    }
    Node* current = list->head;
    do {
        printf("%.2f -> ", current->data);
        current = current->next;
    } while (current != list->head);
    printf("(head)\n");
}
