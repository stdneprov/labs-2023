#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

int TreePushR(Node** root, Node *node) {
    if (*root == NULL) {
        *root = node;
        return 1;
    } else if ((*root)->value->type != OPERATOR){
        return 0;
    } else if (TreePushR(&((*root)->r), node)) {
        return 1;
    } else if (TreePushR(&((*root)->l), node)) {
        return 1;
    } else {
        return 0;
    }
}

void TreePush(Node **root, T* value) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->value = value;
    node->l = NULL;
    node->r = NULL;
    if (*root == NULL) {
        *root = node;
    } else {
        TreePushR(root, node);
    }
}

void TreeDestroy(Node *root) {
    if (root != NULL) {
        TreeDestroy(root->l);
        TreeDestroy(root->r);
        DelItem(root->value);
        free(root);
    }
}

int EqualTrees(Node *root1, Node *root2) {
    if ((root1 == NULL) || (root2 == NULL)) return 0;
    if (root1->value->type != root2->value->type) return 0;

    if ((root1->value->type == NUMBER)) {
        return (root1->value->value.number == root2->value->value.number);
    } else if ((root1->value->type == OPERATOR)){
        return ((root1->value->value.operator.c == root2->value->value.operator.c) && EqualTrees(root1->l, root2->l) && EqualTrees(root1->r, root2->r));
    } else if ((root1->value->type == VARIABLE)){
        if (root1->value->value.str->lenStr != root2->value->value.str->lenStr) return 0;
        char* s1 = root1->value->value.str->chars;
        char* s2 = root2->value->value.str->chars;
        for (int i = 0; i < root1->value->value.str->lenStr; i++) {
            if (s1[i] != s2[i]) return 0;
        }
        return 1;
    }
}

void PrintTree(Node *root, int depth) {
    for(int i = 0; i < depth; i++) {
        printf("   ");
    }
    PrintItem(root->value);
    printf("\n");
    if (root->l != NULL) {
        PrintTree(root->l, depth + 1);
    }
    if (root->r != NULL) {
        PrintTree(root->r, depth + 1);
    }
}

void PrintTreeD(Node *root) {
    printf("------------\n");
    PrintTree(root, 0);
    printf("------------\n");
}

