#ifndef LIST_H
#define LIST_H

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* NewNode(int data);
Node* FindNode(Node* head, int key);
void PushFront(Node** head_ref, int data);
void DeleteNode(Node** head_ref, int key);
int IsEmpty(Node* head);
void FreeList(Node** head_ref);
void PrintList(Node* node);
void InsertAfterValue(Node** head_ref, int value, int data);

#endif
