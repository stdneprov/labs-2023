#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>



typedef struct BinaryTree {
    int data;
    struct BinaryTree *left;
    struct BinaryTree *right;
    int depth;
} Tree;

int maxDepth = 0;
int ball = 0;

Tree *createdNode(int data) {
    Tree *newNode = (Tree *)malloc(sizeof(Tree)); 
    
    if (newNode == NULL) {
        printf("Malloc returned 0\n");
        exit(1);
    }

    
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->depth = 0;
    return newNode;
}
int elemInTree = 0;

void Push(Tree** root, int value) {
    Tree* newNode = createdNode(value);
    int d = 0;
    if (*root == NULL) {
        *root = newNode;
        return;
    }

    Tree* current = *root;
    while (1) {
        if (value < current->data) {
            ++d;
            if (current->left == NULL) {
                current->left = newNode;
                current->left->depth = d;
                if (maxDepth < d) {
                    maxDepth = d;
                }
                break;
            } else {
                current = current->left;
            }
        } else if (value > current->data) {
            ++d;
            if (current->right == NULL) {
                current->right = newNode;
                current->right->depth = d;
                if (maxDepth < d) {
                    maxDepth = d;
                }
                break;
            } else {
                current = current->right;
            }
        } else {
            elemInTree = 1;
            break;
        }
    }
}

void PrintNode(Tree *root, int indent) {
    if (root == NULL) {
        return;     
    }
    indent += 1;
    PrintNode(root->left, indent);     
    for (int i = 0; i < indent; ++i){
        printf(" ");
    }
    printf("%d\n", root->data);  
    PrintNode(root->right, indent); 
}

void PrintInDepthRecursively(Tree *root){
    PrintNode(root, 0);
}

void Balance(Tree* root) {
    if (root == NULL) {
        printf("Дерева нет\n");
        return;
    } else {
        if ((root->left == NULL) && (root->right == NULL) && (root->depth != maxDepth)) {
            ball = 2;
            //printf("Дерево не сбалансированно\n");
            return;
        }
        if ((root->left != NULL) && (root->right == NULL)) {
            //printf("Дерево не сбалансированно\n");
            ball = 2;
            return;
        }
        if ((root->left == NULL) && (root->right != NULL)) {
            //printf("Дерево не сбалансированно\n");
            ball = 2;
            return;
        }
        if ((root->left != NULL)) {
            Balance(root->left);
        }
        if ((root->right != NULL)) {
            Balance(root->right);
        }
    }
    if (ball != 2) {
        ball = 1;
    }
}

void Hello() {
    printf("Это меню управления программой\n");
    printf("Если хочешь добавить значение - введи push и в следующей строке значение\n");
    printf("Если хочешь проверить сбалансированность - введи balance\n");
    printf("Если хочешь посмотреть дерево - введи print\n");
    printf("Если хочешь узнать глубину - введи depth\n");
    printf("Если хочешь удалить значение - введи delete и в следующей строке значение\n");
    printf("Если хочешь выйти - введи exit или ctrl+D\n");
    printf("В случае неверной команды ничего не произойдет\n");
}

int haveNode = 0;
int errorNode = 0;

struct BinaryTree* deleteNode(Tree* root, int key) {
    struct BinaryTree *parent = NULL, *current = root;

    while (current != NULL && current->data != key) {
        parent = current;
        if (key < current->data) {
            current = current->left;
        } else {
            current = current->right;
        }
    }

    if (current == NULL) {
        printf("Элемент в дереве не найден\n");
        errorNode = 1;
        return root;
    }

    if (current->left == NULL && current->right == NULL) {
        if (parent == NULL) {
            free(current);
            return NULL;
        }
        if (parent->left == current) {
            parent->left = NULL;
        } else {
            parent->right = NULL;
        }
        free(current);
    } else if (current->left == NULL) {
        if (parent == NULL) {
            root = current->right;
            free(current);
            return root;
        }
        if (parent->left == current) {
            parent->left = current->right;
        } else {
            parent->right = current->right;
        }
        free(current);
    } else if (current->right == NULL) {
        if (parent == NULL) {
            root = current->left;
            free(current);
            return root;
        }
        if (parent->left == current) {
            parent->left = current->left;
        } else {
            parent->right = current->left;
        }
        free(current);
    } else {
        struct BinaryTree* successor = current->right;
        struct BinaryTree* successorParent = current;
        while (successor->left != NULL) {
            successorParent = successor;
            successor = successor->left;
        }
        current->data = successor->data;
        if (successorParent->left == successor) {
            successorParent->left = successor->right;
        } else {
            successorParent->right = successor->right;
        }
        free(successor);
    }

    return root;
}

int hasElements(Tree* root) {
    if(root == NULL) {
        return 0;
    } else {
        return 1;
    }
}

int Depth(Tree** root, int value) {

    Tree* current = *root;
    while (1) {
        if (value < current->data) {
            if (current->left == NULL) {
                break;
            } else {
                current = current->left;
            }
        } else if (value > current->data) {
            if (current->right == NULL) {
                break;
            } else {
                current = current->right;
            }
        } else {
            return current->depth;
        }
    }
}

void Find(Tree** root, int value) {
    Tree* newNode = createdNode(value);
    if (*root == NULL) {
        elemInTree = 0;
        return;
    }

    Tree* current = *root;
    while (1) {
        if (value < current->data) {
            if (current->left == NULL) {
                break;
            } else {
                current = current->left;
            }
        } else if (value > current->data) {
            if (current->right == NULL) {
                break;
            } else {
                current = current->right;
            }
        } else {
            elemInTree = 1;
            break;
        }
    }
}

void Menu() {
    Hello();
    Tree *BinaryTree = NULL;

    char inputUser[10] = "";


    while(!feof(stdin)) {
        char inputUser[10] = "";
        fgets(inputUser, sizeof(char) * 10, stdin);
        fflush(stdin);
        if (strcmp(inputUser, "print\n") == 0) {
            if (haveNode == 0) {
                printf("Дерево не задано\n");
            } else {
                printf("Бинарное дерево\n");
                PrintInDepthRecursively(BinaryTree);
                printf("\n");
            }

        } else if (strcmp(inputUser, "balance\n") == 0){
            printf("%d\n", maxDepth);
            if (haveNode == 0) {
                printf("Дерево не задано\n");
            } else {
                Balance(BinaryTree);
                if (ball != 1) {
                    printf("Дерево не сбалансированно\n");
                    ball = 0;
                } else {
                    printf("Дерево сбалансированно\n");
                    ball = 0;
                }
            }
            continue;
        } else if (strcmp(inputUser, "push\n") == 0) {
            printf("Введите значение элемента: ");
            int number = 0;
            scanf("%d", &number);
            Push(&BinaryTree, number);
            haveNode = 1;
            if (elemInTree == 1) {
                printf("Элемент уже существует в дереве\n");
                elemInTree = 0;
            }
            else {
                printf("Элемент добавлен\n");
            }

            continue;
        } else if (strcmp(inputUser, "depth\n") == 0) {
            printf("Введите значение элемента: ");
            int number = 0;
            scanf("%d", &number);
            Find(&BinaryTree, number);
            haveNode = 1;
            if (elemInTree != 1) {
                printf("Элемента нет в дереве\n");
                elemInTree = 0;
            }
            else {
                printf("глубина элемента = ");
                printf("%d\n", Depth(&BinaryTree, number));
            }

            continue;
        } else if ((strcmp(inputUser, "exit\n") == 0)) {
            break;
        } else if ((strcmp(inputUser, "delete\n") == 0)) {
            if (haveNode == 0) {
                printf("Дерево не задано\n");
            } else {
                printf("Введите значение элемента: ");
                int number = 0;
                scanf("%d", &number);
                BinaryTree = deleteNode(BinaryTree, number);
                if (errorNode != 1) {
                    printf("Элемент удален\n");

                } else {
                    errorNode = 0;
                }

                if (hasElements(BinaryTree) == 0) {
                    haveNode = 0;
                }
            }
        }
    }

}

int main() {
    Menu();
    printf("%d", maxDepth);
    return 0;

}