#include <stdio.h>
#include <stdlib.h>


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

int main() {
    Tree *BinaryTree = NULL;
    Push(&BinaryTree, 4);
    // Push(&binaryTree, 3);
    Push(&BinaryTree, 7);
    // Push(&binaryTree, 4);
    Push(&BinaryTree, 5);
    Push(&BinaryTree, 6);
    // Push(&BinaryTree, 1);
    PrintInDepthRecursively(BinaryTree);
    if (IsLinear(BinaryTree)) {
        printf("Двоичное дерево является линейным списком");
    } else {
        printf("Двоичное дерево не является линейным списком");
    }
    return 0;

}
