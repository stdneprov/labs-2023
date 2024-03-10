#ifndef __TREE__
#define __TREE__
#include <stdbool.h>

typedef struct Node {
    int key;
    struct Node *left;
    struct Node *right;
    struct Node *parents;
    
} Node;

Node *CreateNode(int value);
void TreePush(Node *root, int indent);
Node *TreeSearch(Node *root, int value);
Node *TreeAdd(Node *root, int value);
Node *TreeDeleteNode(Node *root, int value);
int GetTreeRoot(Node *root);
int IsSimilarity(Node *root);
int GetDepthTree(Node *root, int deep);
bool TreeSimilarity(Node *root);

#endif