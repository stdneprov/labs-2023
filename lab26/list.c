#include "list.h"

Node* NewNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("malloc error\n");
        return NULL;
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

Node* FindNode(Node* head, int key) {
    Node* current = head;
    while (current != NULL) {
        if (current->data == key)
            return current;
        current = current->next;
    }
    return NULL; 
}

void PushFront(Node** head_ref, int data) {
    Node* new_node = NewNode(data);
    new_node->next = *head_ref;
    *head_ref = new_node;
}

void DeleteNode(Node** head_ref, int key) {
    Node* temp = *head_ref;
    Node* prev = NULL;

    if (temp != NULL && temp->data == key) {
        *head_ref = temp->next;
        free(temp);
        return;
    }

    while (temp != NULL && temp->data != key) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL)
        return;

    prev->next = temp->next;
    free(temp);
}

int IsEmpty(Node* head) {
    return (head == NULL);
}

void FreeList(Node** head_ref) {
    Node* current = *head_ref;
    Node* next;
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
    *head_ref = NULL;
}

void PrintList(Node* node) {
    while (node != NULL) {
        printf("%d ", node->data);
        node = node->next;
    }
    printf("\n");
}

void InsertAfterValue(Node** head_ref, int value, int data) {
    Node* current = *head_ref;
    while (current != NULL) {
        if (current->data == value) {
            Node* new_node = NewNode(data);
            new_node->next = current->next;
            current->next = new_node;
            return;
        }
        current = current->next;
    }
    printf("node not found\n");
}

