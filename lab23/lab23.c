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
    Tree *newNode = (Tree *)malloc(sizeof(Tree));
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
int elemInTree = 0;

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
        } else if (value > current->data) {
            if (current->right == NULL) {
                current->right = newNode;
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

//Рекурсивный обход дерева в глубину
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

void Hello() {
    printf("Меню управления программой\n");
    printf("Добавить значение - add\n");
    printf("Посмотреть дерево - print\n");
    printf("Узнать глубину дерева - len\n");
    printf("Удалить значение - delete\n");
    printf("Выйти - exit или ctrl+D\n");
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

int FindDepth(struct BinaryTree* root) {
    if (root == NULL) {
        return 0;
    } else {
        int leftDepth = FindDepth(root->left);
        int rightDepth = FindDepth(root->right);

        // Возвращаем максимальную глубину из левого и правого поддеревьев
        return (leftDepth > rightDepth) ? (leftDepth + 1) : (rightDepth + 1);
    }
}

//Меню управления
void Menu() {
    Hello();
    Tree *BinaryTree = NULL;

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
            
        }
        else if (strcmp(inputUser, "len\n") == 0){
            printf("Глубина двоичного дерева: %d\n", FindDepth(BinaryTree));
        }
        else if (strcmp(inputUser, "add\n") == 0) {
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
        }
        else if ((strcmp(inputUser, "exit\n") == 0)) {
            break;
        }
        
        else if ((strcmp(inputUser, "delete\n") == 0)) {
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
