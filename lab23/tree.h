#ifndef __TREE__
#define __TREE__
#include<stdbool.h>
typedef struct Node {
    int value;
    struct Node *l;
    struct Node *r;
} Node;

Node *CreateNode(int value);
void TreePush(Node **root);
void TreePop(Node **root);
void Free(Node** tree);
#endif