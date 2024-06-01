#ifndef LIST_H
#define LIST_H

typedef struct Node {
    float data;
    struct Node* next;
} Node;

typedef struct Iterator {
    Node* node;
} Iterator;

Node* CreateNode(float data);
Iterator CreateList();
Iterator Next(Iterator iter);
void InsertAfter(Iterator* iter, float data);
void Push(Iterator* iter, float data); 
void DeleteNode(Iterator* iter, float value);
void FreeList(Iterator iter);
int ListLength(Iterator iter);
void ClearListIfExists(Iterator* iter, float value);
void PrintList(Iterator iter);

#endif 
