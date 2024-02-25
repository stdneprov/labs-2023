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
void Push(Tree **treeBinary, int data) {

    Tree *tmp = *treeBinary;
    //Если бинарное дерево равно NULL
    if (tmp == NULL) {
        *treeBinary = createdNode(data);
    }
    else if (data < tmp->data) {
        if (tmp->left == NULL) {
            tmp->left = createdNode(data);
        } else {
            Push(&(tmp->left), data);
        }
    }
    else if (data > tmp->data) {
        if (tmp->right == NULL) {
            tmp->right = createdNode(data);
        } else {
            Push(&(tmp->right), data);
        }
    }
}

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
    if (root == NULL) {
        return 1;
    }

    if (root->left && root->right) {
        return 0;
    }

    if (root->left) {
        return IsLinear(root->left);
    } else if (root->right) {
        return IsLinear(root->right);
    }
    return 1;
}

void Hello() {
    printf("Это меню управления программой\n");
    printf("Если хочешь добавить значение - введи push и в следующей строке значение\n");
    printf("Если хочешь проверить линейность - введи linear\n");
    printf("Если хочешь посмотреть дерево - введи print\n");
    printf("Если хочешь выйти - введи exit\n");
    printf("В случае неверной команды ничего не произойдет\n");
}
//Меню управления
void Menu() {
    Hello();
    Tree *BinaryTree = NULL;
    char inputUser[10] = "";
    int haveNode = 0;

    while(strcmp(inputUser, "exit") != 0) {
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
        } else if (strcmp(inputUser, "exit\n") == 0) {
            break;
        }
    }
}

int main() {
    Menu();
    return 0;

}
