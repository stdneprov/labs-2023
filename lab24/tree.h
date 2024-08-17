#ifndef TREE_H
#define TREE_H
#include <stdbool.h>
#include "stack.h"

typedef struct Node  {
    type type;
    variable data;
    struct Node *left;
    struct Node *right;

} Node;

Node *CreateNode(variable value, type type);
void TreePrint(Node *root, int indent);
Node *FindNode(Node *root, variable value);
Node *AddNode(Node *root, variable value, type type);
void TreeFree(Node *root);

#endif