#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node Node;


struct Node {
    int val;
    struct Node *left;
    struct Node *right;
};

Node tree;
int wasCreated = 0;

//Добавление нового узла
Node *CreateNode(int value){
    Node *ptrNode = malloc(sizeof(Node));
    if (ptrNode != NULL) {
        ptrNode->left = NULL;
        ptrNode->right = NULL;
        ptrNode->val = value;
        return ptrNode;
    } else {
        exit(-1);
    }
}

void AddNode(Node *root, int value) {
    while (1) {
        if (root->val == value){
            // такое значение уже существует, ничего не делаем
            break;
        }

        else if (root->val < value) {
            if (root->right != NULL){
                root = root->right;
            }
            else{
                root->right = CreateNode(value);
                break;
            }
        }

        else if (root->val > value){
            if (root->left != NULL){
                root = root->left;
            }
            else{
                root->left = CreateNode(value);
                break;
            }
        }

    }
}


//Вывод дерева
void PrintNode(Node *root, int indent) {
    if (root == NULL) {
        return;     
    }
    indent += 1;
    PrintNode(root->left, indent);     
    for (int i = 0; i < indent; ++i){
        printf(" ");
    }
    printf("%d\n", root->val);  
    PrintNode(root->right, indent); 
}

void PrintTree(Node *root){
    PrintNode(root, 0);
}

//Удаление элемента
int FindValueForRight(Node *root, Node *parent, int value) {
    while (1){
        if (root->left != NULL) {
            parent = root;
            root = root->left;
        } else {
            if (parent->right != NULL) {
                if (parent->right->val == root->val && root->right == NULL) {
                    parent->right = NULL;
                    printf("-The value has been deleted\n");
                    return root->val;
                } else if (parent->right->val == root->val && root->right != NULL) {
                    parent->right = root->right;
                    printf("-The value has been deleted\n");
                    return root->val;
                }
            }
            if (root->right == NULL) {
                parent->left = NULL;
            } else {
                parent->left = root->right;
            }
            printf("-The value has been deleted\n");
            return root->val;
        }
    }
    return 0;
}

int FindValueForLeft(Node *root, Node *parent, int value) {
    while (1) {
        if (root->right != NULL) {
            parent = root;
            root = root->right;
        } else {
            if (parent->left != NULL) {
                if (parent->left->val == root->val && root->left == NULL) {
                    parent->left = NULL;
                    printf("-The value has been deleted\n");
                    return root->val;
                } else if (parent->left->val == root->val && root->left != NULL) {
                    parent->left = root->left;
                    printf("-The value has been deleted\n");
                    return root->val;
                }
            }
            if (root->left == NULL) {
                parent->right = NULL;
            } else {
                parent->right = root->left;
            }
            printf("-The value has been deleted\n");
            return root->val;
        }
    }
    return 0;
}

void DeleteNode(Node *root, Node *parent, int value){
    while (1) { 
        if (root->val == value){
            if (root->right == NULL && root->left == NULL) {
                if (parent->val < value){
                    parent->right = NULL;
                    free(root);
                } else if (parent->val > value){
                    parent->left = NULL;
                    free(root);
                } else if (parent->val == root->val) {
                    root->val = 0;
                    wasCreated = 0;
                }
                printf("-Value was deleted\n");
                break;
            } else if(root->right != NULL) {
                root->val = FindValueForRight(root->right, root, value);
                break;
            } else if(root->left != NULL) {
                root->val = FindValueForLeft(root->left, root, value);
                break;
            }
        } else if (root->val < value) {
            if (root->right == NULL) {
                printf("-There is no such value\n");
                break;
            } else {
                root = root->right;
            }
        } else if (root->val > value) {
            if (root->left == NULL) {
                printf("-There is no such value\n");
                break;
            } else {
                root = root->left;
            }
        }
    }
}

//Проверка симметричности
int CompareNodes(Node *left, Node *right){
    if (left->left != NULL && right->right != NULL && left->right != NULL && right->left != NULL)
    {
        CompareNodes(left->left, right->right);
        CompareNodes(left->right, right->left);
    } else if (left->left != NULL && right->right != NULL && left->right == NULL && right->left == NULL){
        CompareNodes(left->left, right->right);
    } else if (left->right != NULL && right->left != NULL && left->left == NULL && right->right == NULL) {
        CompareNodes(left->right, right->left);
    } else if (left->left == NULL && right->right == NULL && left->right == NULL && right->left == NULL){
        // это лист, с ним ничего не делаем
    } else {
        return 1;
    }
    return 0;
}

void IsSymmetric(Node *root){
    if (CompareNodes(root->left, root->right) == 1){
        printf("-NO\n");
    } else {
        printf("-YES\n");
    }
}

//Меню
void Menu() {

    char input[20];
    char addCommand[10] = "add";
    char showCommand[10] = "show";
    char deleteCommand[10] = "delete";
    char symmetryCommand[10] = "symmetric";
    char exitCommand[10] = "exit";
    char command[10] = "";

    while(strcmp(command, exitCommand) != 0) {
        printf("----------------------------------------------------------------------\n");
        printf("$ add value - will add value (instead \"value\" type your number)\n");
        printf("$ show - will show tree\n");
        printf("$ delete value - will delete value (instead \"value\" type your number)\n");
        printf("$ symmetric - will check symmetry\n");
        printf("$ exit - stop program\n");
        printf("----------------------------------------------------------------------\n");

        char command[10] = "";
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
        
        
        if (strcmp(command, addCommand) == 0) {
            if (wasCreated == 0) {
                tree.val = num;
                wasCreated = 1;
                printf("-Value added\n");
            } else {
                AddNode(&tree, num);
                printf("-Value added\n");
            }
        } else if (strcmp(command, showCommand) == 0) {
            if (wasCreated == 0){
                printf("-Tree doesn't exist\n");
            } else {
                PrintTree(&tree);
            }
        } else if (strcmp(command, symmetryCommand) == 0) {
            if (wasCreated == 0){
                printf("-Tree doesn't exist\n");
            } else {
                IsSymmetric(&tree);
            }
        } else if (strcmp(command, deleteCommand) == 0) {
            DeleteNode(&tree, &tree, num);
        } else  if (strcmp(command, exitCommand) == 0) {
            break;
        } else {
            printf("-Wrong command\n");
        }
    }
}

int main() {
    Menu();
}
