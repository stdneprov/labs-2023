#ifndef __TREE_AND_STACK__
#define __TREE_AND_STACK__
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>



struct Token{
    unsigned value;
    char operation;
    unsigned tokentype;
};

struct Stack{
    struct Token* nodes;
    unsigned capacity; //зарезервированная память
    unsigned size; //размер
};

struct Node{
    struct Token object;
    struct Node* right;
    struct Node* left;
};

struct Tree {
    struct Node* root;
};

struct Token Pop(struct Stack* q);
void InitStack(struct Stack* q);
void PushBack(struct Stack* q, struct Token element);
struct Token Peak(struct Stack* q);
int PriorityOfOperation(char a);
void PrintStack(struct Stack* s);
void InitTree(struct Tree* t);
struct Node* SubInsert(struct Node* node, struct Stack* s);
void Insert(struct Tree* t, struct Stack* s);
void PrintElement(struct Token element);
void PrintTree(struct Node* node);
void SubFreeTree(struct Tree* t,struct Node* node);
void FreeTree(struct Tree* t);




#endif