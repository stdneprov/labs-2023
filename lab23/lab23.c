#include <stdio.h>
#include <stdlib.h>

// Структура для представления узла в двоичном дереве
struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

// Функция для создания нового узла
struct Node* CreateNode(int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Функция для определения глубины двоичного дерева
int FindDepth(struct Node* root) {
    if (root == NULL) {
        return 0;
    } else {
        int leftDepth = FindDepth(root->left);
        int rightDepth = FindDepth(root->right);

        // Возвращаем максимальную глубину из левого и правого поддеревьев
        return (leftDepth > rightDepth) ? (leftDepth + 1) : (rightDepth + 1);
    }
}

int main() {
    struct Node* root = CreateNode(1);
    root->left = CreateNode(2);
    root->right = CreateNode(3);
    root->left->left = CreateNode(4);
    root->left->right = CreateNode(5);
    root->left->right->left = CreateNode(77);

    printf("Глубина двоичного дерева: %d\n", FindDepth(root));

    return 0;
}
