#ifndef __TREE__
#define __TREE__
#include "item.h"

typedef Item T;

typedef struct Node {
    T* value;
    struct Node *l;
    struct Node *r;
} Node;

void TreePush(Node **root, T* value);
void TreeDestroy(Node *root);
int EqualTrees(Node *root1, Node *root2);
void PrintTreeD(Node *root);


#endif