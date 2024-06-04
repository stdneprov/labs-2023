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

Iterator CreateList() {
    Iterator list;
    list.node = NULL;
    return list;
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
    }
    if (iter->node == NULL) {  // пустой список
        newNode->next = newNode;  // указывает сам на себя
        iter->node = newNode;
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
    if (iter->node == NULL) {
        newNode->next = newNode;
        iter->node = newNode;
    } else {
        Node* current = iter->node;
        while (current->next != iter->node) {
            current = current->next;
        }
        current->next = newNode;  // в конец списка
        newNode->next = iter->node;  // некст на начало списка
        iter->node = newNode; 
    }
}

void DeleteNode(Iterator* iter, float value) {
    if (iter->node == NULL) { 
        printf("list is empty\n");
        return;
    }
    Node* current = iter->node;
    Node* prev = NULL;
    do {
        if (current->data == value) {
            if (prev == NULL) { 
                if (current->next == current) {  // единственный элемент
                    free(current);
                    iter->node = NULL;
                } else {
                    Node* tail = current;
                    while (tail->next != current) {
                        tail = tail->next;
                    }
                    iter->node = current->next;
                    tail->next = iter->node;
                    free(current);
                }
            } else {
                prev->next = current->next;
                if (current == iter->node) { 
                    iter->node = current->next;
                }
                free(current);
            }
            return;
        }
        prev = current;
        current = current->next;
    } while (current != iter->node);
    printf("value not found\n");
}

void FreeList(Iterator iter) {
    while (iter.node != NULL && iter.node->next != iter.node) {
        Iterator i = Next(iter);
        DeleteNode(&i, i.node->data);
    }
    if (iter.node != NULL) {  // первый узел
        free(iter.node);
        iter.node = NULL;
    }
}

int ListLength(Iterator iter) {
    if (iter.node == NULL) {
        printf("list is empty\n");
        return 0;
    }
    int length = 0;
    Node* current = iter.node;
    do {
        length++;
        current = current->next;
    } while (current != iter.node);
    return length;
}

void ClearListIfExists(Iterator* iter, float value) {
    if (iter->node == NULL) {
        return;
    }
    Node* current = iter->node;
    do {
        if (current->data == value) {
            FreeList(*iter);
            iter->node = NULL;
            printf("value found. the list is cleared\n");
            return;
        }
        current = current->next;
    } while (current != iter->node);
    printf("value not found\n");
}

void PrintList(Iterator iter) {
    if (iter.node == NULL) {
        printf("list is empty\n");
        return;
    }
    Node* current = iter.node;
    do {
        printf("%.2f -> ", current->data);
        current = current->next;
    } while (current != iter.node);
    printf("(head)\n");
}
