#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"

Node *CreateNode(variable value, type type) {
    Node *tmp = (Node *)malloc(sizeof(Node));
    if (tmp == NULL) {
        exit(-1);
    }

    tmp->data = value;
    tmp->left = NULL;
    tmp->right = NULL;
    tmp->type = type;
    return tmp;
}

Node *AddNode(Node *root, variable value, type type) {
    Node *tmp = (Node *)malloc(sizeof(Node));
    if (tmp == NULL) {
        exit(-1);
    }
    tmp->data = value;
    tmp->type = type;
    tmp->right = NULL;
    tmp->left = NULL;

    return tmp;
}

void TreePrint(Node *root, int indent) {
    if (root == NULL) {
        return;
    }

    indent += 4;

    TreePrint(root->right, indent);

    for (int i = 4; i < indent; ++i) {
        printf(" ");
    }
    if (root->type == NUM) {
        printf("%d\n", root->data.num);  
    } else if (root->type == VAR) {
        printf("%s\n", root->data.symb); 
    } else {
        printf("%c\n", *root->data.symb);
    }

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
