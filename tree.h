#ifndef _TREE
#define _TREE
#include <stdio.h>
#include <stdlib.h>

typedef struct Node Node;
typedef union Value Value;
typedef Node* Tree;

union Value {
    char oper;
    int num;
    char var;
};

enum Type {
    OPER, NUM, VAR
};

struct Node {
    Node* lvalue;
    Node* rvalue;

    Value val;
    enum Type type;
};

Tree InitTree();
void Clear(Node** tree);
int Add(Node** parent, Value val, enum Type type);
int Del(Node** targ);
void PrintTree(Tree ptr, int depth);
void PrintExpression(Tree ptr);

#endif