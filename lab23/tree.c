#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"

#define NOT_LEFT_LIST  0
#define NOT_RIGHT_LIST 1
#define NOT_LIST 2


Node *CreateNode(int value) {
    Node *tmp = (Node *)malloc(sizeof(Node));
    if (tmp == NULL) {
        exit(-1);
    }

    tmp->key = value;
    tmp->left = NULL;
    tmp->right = NULL;
    tmp->parents = NULL;
    return tmp;
}

int GetTreeRoot(Node *root) {
    Node *root2 = root;
    Node *root3 = root;
    while (root2 != NULL) {
        root3 = root2;
        root2 = root2->parents;
    }
    return root3->key;
    
}

Node *TreeAdd(Node *root, int value) {
    Node *root2 = root;
    Node *root3 = NULL;
    Node *tmp = (Node *)malloc(sizeof(Node));
    tmp->key = value;
    while (root2 != NULL) {
        root3 = root2;
        if (value < root2->key) {
            root2 = root2->left;
        } else {
            root2 = root2->right;
        }
    }

    tmp->parents = root3;
    tmp->right = NULL;
    tmp->left = NULL;
    if (value < root3->key) {
        root3->left = tmp;
    } else {
        root3->right = tmp;
    }
    return root;
}

Node *TreeSearch(Node *root, int value) {
    if (root == NULL || value == root->key) {
        return root;
    }

    while (root->key != value){
        if (value < root->key){
            root = root->left;
        } else {
            root = root->right;
        }
    }
    return root;
}

void TreePush(Node *root, int indent) {
    if (root == NULL) {
        return;
    }
    for (int i = 0; i < indent; ++i){
        printf(" ");
    }
    if (root->key) {
        printf("%d\n ", root->key);
    }
    indent++;
    TreePush(root->left, indent);

    TreePush(root->right, indent);
}

Node *TreeDeleteNode(Node *root, int value) {
    Node *deletedNode = NULL;
    deletedNode = TreeSearch(root, value);
    if (deletedNode->left == NULL && deletedNode->right == NULL) {
        if(deletedNode == deletedNode->parents->right) {
            deletedNode->parents->right = NULL;
        } else {
            deletedNode->parents->left = NULL;
        }
        free(deletedNode);
    } else if (deletedNode->left == NULL) {
        if (deletedNode->parents->left->key == deletedNode->key){
            deletedNode->parents->left = deletedNode->right;
            deletedNode->right->parents = deletedNode->parents; 
        } else {
            deletedNode->parents->right = deletedNode->right;
            deletedNode->right->parents = deletedNode->parents; 
        }
        free(deletedNode);
    } else if (deletedNode->right == NULL) {
        if (deletedNode->parents->right->key == deletedNode->key){
            deletedNode->parents->right = deletedNode->left;
            deletedNode->left->parents = deletedNode->parents; 
        } else {
            deletedNode->parents->right = deletedNode->right;
            deletedNode->right->parents = deletedNode->parents; 
        }
        free(deletedNode);
    } else {
        int val = GetTreeRoot(deletedNode);
        Node *root2 = deletedNode;
        Node *root3 = NULL;
        if (deletedNode->key < val) {
            root2 = deletedNode->right;
            while (root2 != NULL) {
                root3 = root2;
                root2 = root2->left;
            }
            deletedNode->key = root3->key;
            if (root3->right) {
                root3->right->parents = root3->parents;
                root3->parents->left = root3->right;
            } else if ((root3->left == NULL) && (root3->right == NULL)) {
                root3->parents->right = NULL;
            }
            else {
                root3->parents->left = NULL;
            }
            free(root3);
        } else {
            root2 = deletedNode->left;
            while (root2 != NULL) {
                root3 = root2;
                root2 = root2->right;
            }
            deletedNode->key = root3->key;
            if (root3->left) {
                root3->left->parents = root3->parents;
                root3->parents->right = root3->left;
            } else if ((root3->left == NULL) && (root3->right == NULL)) {
                root3->parents->left = NULL;
            } else {
                root3->parents->right = NULL;
            }
            free(root3);
        }
    }

    return root;
}

int GetDepthTree(Node *root, int deep) {
    int depth = deep;
    if (root->left != NULL && root->right != NULL) {
        GetDepthTree(root->left, depth + 1);
        GetDepthTree(root->right, depth + 1);
    } else {
        return depth;
    }
}

int IsSimilarity(Node *root) {
    if (root->left != NULL && root->right != NULL) {
        IsSimilarity(root->left);
        IsSimilarity(root->right);
    } else if ((root->left == NULL && root->right != NULL)) {
        return NOT_RIGHT_LIST; // нет правого листа
    } else if ((root->right == NULL && root->left != NULL)) {
        return NOT_LEFT_LIST; // нет левого листа
    }
    else {
        return NOT_LIST; // нет правого и левого
    }
}

bool TreeSimilarity(Node *root) {
    int depthLeft = GetDepthTree(root->left, 1);
    int depthRight = GetDepthTree(root->right, 1);
    if (depthLeft == depthRight) {
        if (IsSimilarity(root->left) == NOT_LEFT_LIST && IsSimilarity(root->right) == NOT_RIGHT_LIST) {
            return 1;
        } else if (IsSimilarity(root->left) == NOT_RIGHT_LIST && IsSimilarity(root->right) == NOT_LEFT_LIST){
            return 1;
        } else {
            return 0;
        }
    }
}


int main() {
    char input[20];
    char addNode[10] = "add";
    char createTree[10] = "create";
    char pushTree[10] = "push";
    char deleteNode[10] = "delete";
    char checkSimilarity[15] = "similarity";
    char exitMenu[10] = "exit";
    char command[10] = "";

    while(strcmp(command, exitMenu) != 0) {
        printf("\n");
        printf("====================================================================\n");
        printf("# create value - create with value in root\n");
        printf("# add value - add value\n");
        printf("# push - push tree\n");
        printf("# delete value - will delete value\n");
        printf("# similarity - check similarity\n");
        printf("# exit - stop programm\n");
        printf("====================================================================\n");

        char command[15] = "";
        fgets(input, sizeof(char) * 20, stdin);
        if (feof(stdin)) {
            break;
        }
        int num = 0;

        for (int i = 0; input[i] != '\n'; ++i) {
            if (input[i] != ' ' && input[i] !='\n') {
                command[i] = input[i];
                input[i] = ' ';
            }
            else {
                break;
            }
        }
        num = strtol(input, NULL, 10);
        
        Node tree;
        if (strcmp(command, createTree) == 0) {
            tree = *CreateNode(num);
        } else if (strcmp(command, pushTree) == 0) {
            TreePush(&tree, 0);
        } else if (strcmp(command, addNode) == 0) {
            TreeAdd(&tree, num);
        } else if (strcmp(command, deleteNode) == 0) {
            TreeDeleteNode(&tree, num);
        } else if (strcmp(command, checkSimilarity) == 0) {
            printf("%d",TreeSimilarity(&tree));
        } else  if (strcmp(command, exitMenu) == 0) {
            break;
        } else {
            printf("-Wrong command\n");
        }
    }
}