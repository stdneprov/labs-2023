#ifndef __TREE__
#define __TREE__
#include <stdio.h>
#include "stack.h"
#include <stdlib.h>
typedef struct Node Node;

typedef struct Node {
    union data value;
    int type;              
    struct Node* left;     
    struct Node* right;    
} Node;

Node* CreateNode(union data value, type type);
Node* AddNode(union data value, type type); 
void PrintNode(Node *root, int indent); 
void PrintTree(Node* tree);
void TreeFree(Node* tree);
#endif 