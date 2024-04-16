#ifndef __TREE__
#define __TREE__
#include <stdbool.h>
#include "stack.h"

typedef struct Node  {
    type type;
    variable key;
    struct Node *left;
    struct Node *right;
    
} Node;

Node *CreateNode(variable value, type type);
void TreePrint(Node *root, int indent);
Node *TreeSearch(Node *root, variable value);
Node *TreeAdd(Node *root, variable value, type type);
void TreeFree(Node *root);

#endif