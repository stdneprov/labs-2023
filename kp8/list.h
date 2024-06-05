#ifndef LIST_H
#define LIST_H

typedef struct Node {
    float data;
    struct Node* next;
} Node;

typedef struct List {
    Node* head;
} List;

typedef struct Iterator {
    Node* node;
    List* list;
} Iterator;

Node* CreateNode(float data);
List CreateList();
Iterator Start(List* list);
Iterator Next(Iterator iter);
void InsertAfter(Iterator* iter, float data);
void Push(Iterator* iter, float data); 
void DeleteNode(Iterator* iter, float value);
void FreeList(List* list);
int ListLength(List* list);
void ClearListIfExists(List* list, float value);
void PrintList(List* list);

#endif
