#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"

Node *CreateNode(variable value, type type) {
    Node *tmp = (Node *)malloc(sizeof(Node));
    if (tmp == NULL) {
        exit(-1);
    }

    tmp->key = value;
    tmp->left = NULL;
    tmp->right = NULL;
    tmp->type = type;
    return tmp;
}


Node *TreeAdd(Node *root, variable value, type type) {
    Node *tmp = (Node *)malloc(sizeof(Node));
    if (tmp == NULL) {
        exit(-1);
    }
    tmp->key = value;
    tmp->type = type;
    tmp->right = NULL;
    tmp->left = NULL;

    return tmp;
}


void TreePrint(Node *root, int indent) {
    if (root == NULL) {
        return;
    }
    indent += 1;   

    for (int i = 0; i < indent; ++i){
        printf("  ");
    }
    if (root->type == NUM) {
        printf("%d\n", root->key.num);  
    } else if (root->type == VAR) {
        printf("%c\n", *root->key.symb);
    } else {
        printf("%c\n", *root->key.symb);
    }
    TreePrint(root->right, indent);  
    TreePrint(root->left, indent); 
}

void TreeFree(Node *root) {
    if (root == NULL) {
        return;
    }
    TreeFree(root->left);
    TreeFree(root->right);
    free(root);
}
