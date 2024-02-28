#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//Структура, представляющая один узел бинарного дерева
typedef struct BinaryTree {
    int data;
    struct BinaryTree *left;
    struct BinaryTree *right;
} Tree;


//функция, создающая узел бинарного дерева
Tree *createdNode(int data) {
    Tree *newNode = (Tree *)malloc(sizeof(Tree)); //динамически выделяем память под структуру
    //проверка на правильность
    if (newNode == NULL) {
        printf("Malloc returned 0\n");
        exit(1);
    }
    
    //заполняем структуру данными
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

//функция, добавляющая элементы в бинарное дерево
void Push(Tree** root, int value) {
    Tree* newNode = createdNode(value);
    if (*root == NULL) {
        *root = newNode;
        return;
    }

    Tree* current = *root;
    while (1) {
        if (value < current->data) {
            if (current->left == NULL) {
                current->left = newNode;
                break;
            } else {
                current = current->left;
            }
        } else {
            if (current->right == NULL) {
                current->right = newNode;
                break;
            } else {
                current = current->right;
            }
        }
    }
}

// void Push(Tree **treeBinary, int data) {

//     Tree *tmp = *treeBinary;
//     //Если бинарное дерево равно NULL
//     if (tmp == NULL) {
//         *treeBinary = createdNode(data);
//     }
//     else if (data < tmp->data) {
//         if (tmp->left == NULL) {
//             tmp->left = createdNode(data);
//         } else {
//             Push(&(tmp->left), data);
//         }
//     }
//     else if (data > tmp->data) {
//         if (tmp->right == NULL) {
//             tmp->right = createdNode(data);
//         } else {
//             Push(&(tmp->right), data);
//         }
//     }
// }

//Рекурсивный обход дерева в глубину
void PrintInDepthRecursively(Tree *BinaryTree) {
    if (BinaryTree == NULL) {
        return;
    } else {
        printf("%d ", BinaryTree->data);
        if (BinaryTree->left != NULL) {
            PrintInDepthRecursively(BinaryTree->left);
        }
        if (BinaryTree->right != NULL) {
            PrintInDepthRecursively(BinaryTree->right); 
        }
    }
}

int IsLinear(Tree* root) {
    if (root->left != NULL && root-> right != NULL) {
        return 0;
    } else if (root->right != NULL) {
        while (root != NULL && root->left == NULL) {
            root = root->right;
        }
    } else {
        while (root != NULL && root->right == NULL) {
            root = root->left;
        }
    }

    return (root == NULL);
}

// int IsLinear(Tree* root) {
//     if (root == NULL) {
//         return 1;
//     }

//     if (root->left && root->right) {
//         return 0;
//     }

//     if (root->left) {
//         return IsLinear(root->left);
//     } else if (root->right) {
//         return IsLinear(root->right);
//     }
//     return 1;
// }

void Hello() {
    printf("Это меню управления программой\n");
    printf("Если хочешь добавить значение - введи push и в следующей строке значение\n");
    printf("Если хочешь проверить линейность - введи linear\n");
    printf("Если хочешь посмотреть дерево - введи print\n");
    printf("Если хочешь удалить значение - введи delete и в следующей строке значение\n");
    printf("Если хочешь выйти - введи exit или cntr+D\n");
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
        printf("Элемент в дереве не найден.\n");
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
// struct BinaryTree* deleteNode(Tree* root, int key) {
//     if (root == NULL) {
//         printf("Дерево не задано");
//         haveNode = 0;
//         return root;
//     }

//     if (key < root->data) {
//         root->left = deleteNode(root->left, key);
//     } else if (key > root->data) {
//         root->right = deleteNode(root->right, key);
//     } else {
//         if (root->left == NULL) {
//             struct BinaryTree* temp = root->right;
//             free(root);
//             // haveNode = 0;
//             return temp;
//         } else if (root->right == NULL) {
//             struct BinaryTree* temp = root->left;
//             free(root);
//             // haveNode = 0;
//             return temp;
//         }

//         struct BinaryTree* temp = root->right;
//         while (temp->left != NULL) {
//             temp = temp->left;
//         }

//         root->data = temp->data;
//         root->right = deleteNode(root->right, temp->data);
//     }
//     // haveNode = 0;
//     return root;
// }

int hasElements(Tree* root) {
    if(root == NULL) {
        return 0;
    } else {
        return 1;
    }
}
//Меню управления
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
            
        } else if (strcmp(inputUser, "linear\n") == 0){
            if (haveNode == 0) {
                printf("Дерево не задано\n");
            } else {
                if (IsLinear(BinaryTree)) {
                    printf("Двоичное дерево является линейным списком\n");
                } else {
                    printf("Двоичное дерево не является линейным списком\n");
                }
            }
        } else if (strcmp(inputUser, "push\n") == 0) {
            printf("Введите значение элемента: ");
            int number = 0;
            scanf("%d", &number);
            Push(&BinaryTree, number);
            haveNode = 1;
            printf("Элемент добавлен\n");
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
    return 0;

}
