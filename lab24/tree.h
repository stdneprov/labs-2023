#ifndef _TREE
#define _TREE
#include <stdio.h>
#include <stdlib.h>

#include "base.h"
#include "stack.h"
typedef struct TreeNode TreeNode;
typedef TreeNode* Tree;
void StackToTree(Stack* expr, TreeNode** node);
Tree InitTree();
void Clear(TreeNode** tree);
int AddInTree(TreeNode** parent, ValueStackNode val, enum TypeStackNode type,
              int priority, int sign);
int DeleteTree(TreeNode** targ);
void PrintTree(Tree ptr, int depth);
void PrintInLine(Tree ptr);
void VariantTree(Tree* tree);
void DivNodeByVar(TreeNode* node, char* target);
void VarOutside(Tree* tree, char target);
void VariantTreeVar(Tree* tree);
void DelOneMulti(Tree* tree);
struct TreeNode {
    TreeNode* lvalue;
    TreeNode* rvalue;
    ValueStackNode val;
    enum TypeStackNode type;
    int priority;
    int sign;
};
#endif