#include <stdio.h>
#include <stdlib.h>

typedef struct Complex {
    double real;
    double imag;
} Complex;

typedef struct Node {
    Complex data;
    struct Node* next;
    struct Node* prev;
} Node;

typedef struct Iterator {
    Node* node;
} Iterator;

Node* createNode(Complex data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Memory allocation error\n");
        return NULL;
    }
    newNode->data = data;
    newNode->next = newNode;
    newNode->prev = newNode;
    return newNode;
}

Iterator createList() {
    Iterator list = {NULL};
    return list;
}

Iterator Next(Iterator it) {
    if (it.node == NULL) {
        printf("Iterator is not initialized\n");
        return it;
    }
    it.node = it.node->next;
    return it;
}

Iterator Prev(Iterator it) {
    if (it.node == NULL) {
        printf("Iterator is not initialized\n");
        return it;
    }
    it.node = it.node->prev;
    return it;
}

void insertAfter(Iterator* it, Complex data) {
    Node* newNode = createNode(data);
    if (newNode == NULL) {
        return;
    }
    if (it->node == NULL) {
        newNode->next = newNode;
        newNode->prev = newNode;
        it->node = newNode;
    } else {
        newNode->next = it->node->next;
        newNode->prev = it->node;
        it->node->next->prev = newNode;
        it->node->next = newNode;
    }
}

void deleteNode(Iterator* it) {
    if (it->node == NULL) {
        printf("Iterator is not initialized\n");
        return;
    }
    it->node->prev->next = it->node->next;
    it->node->next->prev = it->node->prev;
    free(it->node);
    it->node = NULL;
}

void DestroyList(Iterator list) {
    while (list.node != Next(list).node) {
        Iterator d = Next(list);
        deleteNode(&d);
    }
    free(list.node);
    list.node = NULL;
}

int listLength(Iterator list) {
    Node* head = list.node;
    if (head == NULL) {
        printf("List is empty\n");
        return 0;
    }
    int length = 0;
    Node* current = head;
    do {
        length++;
        current = current->next;
    } while (current != head);
    return length;
}

void swapSecondAndPenultimate(Iterator list) {
    Node* head = list.node;
    if (head == NULL || head->next == head || head->next->next == head) {
        printf("List is too short\n");
        return;
    }
    Node* second = head->next;
    Node* penultimate = head->prev->prev;
    Complex buf = second->data;
    second->data = penultimate->data;
    penultimate->data = buf;
}

void PrintList(Iterator list) {
    Node* head = list.node;
    if (head == NULL) {
        printf("List is empty\n");
        return;
    }
    Node* current = head;
    do {
        printf("%.2f + %.2fi\n", current->data.real, current->data.imag);
        current = current->next;
    } while (current != head);
}

int main() {
    Iterator list = createList();

    Complex data1 = {1.0, 1.0};
    insertAfter(&list, data1);
    Iterator it = Next(list);

    Complex data2 = {2.0, 2.0};
    insertAfter(&it, data2);
    it = Next(it);

    Complex data3 = {3.0, 3.0};
    insertAfter(&it, data3);
    it = Next(it);

    Complex data4 = {4.0, 4.0};
    insertAfter(&it, data4);
    it = Next(it);

    Complex data5 = {5.0, 5.0};
    insertAfter(&it, data5);
    it = Next(it);

    printf("List after insertion:\n");
    PrintList(list);

    Iterator d = Prev(it);
    deleteNode(&d);
    printf("List after deletion:\n");
    PrintList(list);

    printf("Length of list: %d\n", listLength(list));

    swapSecondAndPenultimate(list);
    printf("List after swap:\n");
    PrintList(list);

    printf("Check looping\n");
    printf("%.2f + %.2fi\n", it.node->data.real, it.node->data.imag);
    printf("%.2f + %.2fi\n", Next(it).node->data.real, Next(it).node->data.imag);
    printf("%.2f + %.2fi\n", Prev(Next(it)).node->data.real, Prev(Next(it)).node->data.imag);

    DestroyList(list);
    return 0;
}