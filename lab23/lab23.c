#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int index;
    int value;
    struct Node *child;
    struct Node *sibling;
} Node;

int currentIndex = 1;

Node** FindNode(Node *root, int index) {
    if (root == NULL)
        return NULL;

    // если нужный узел - корень
    if (root->index == index) {
        Node **node = (Node**)malloc(2 * sizeof(Node*));
        if (node == NULL) {
            printf("malloc error\n");
            return node;
        }
        node[0] = NULL; // родителя нет
        node[1] = root;
        return node;
    }

    // если нужный узел - ребёнок
    if (root->child != NULL) {
        if (root->child->index == index) {
            Node **node = (Node**)malloc(2 * sizeof(Node*));
            if (node == NULL) {
                printf("malloc error\n");
                return node;
            }
            node[0] = root;
            node[1] = root->child;
            return node;
        }

        // если нужный узел - сиблинг
        Node *temp = root->child;
        while (temp->sibling != NULL) {
            if (temp->sibling->index == index) {
                Node **node = (Node**)malloc(2 * sizeof(Node*));
                if (node == NULL) {
                    printf("malloc error\n");
                    return node;
                }
                node[0] = root;
                node[1] = temp->sibling;
                return node;
            }
            temp = temp->sibling;
        }
    }

    // рекурсивный поиск по детям
    Node **result = FindNode(root->child, index); 
    if (result != NULL)
        return result;

    // по сиблингам
    return FindNode(root->sibling, index); 
}

Node* CreateNode(int value) {
    Node *newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("malloc error\n");
        return newNode;
    }
    newNode->index = currentIndex++;
    newNode->value = value;
    newNode->child = NULL;
    newNode->sibling = NULL;
    return newNode;
}

void AddNode(Node **root) {
    int value;
    printf("enter node value: ");
    scanf("%d", &value);

    // если пока нет корня
    if (*root == NULL) {
        *root = CreateNode(value);

    // если корень уже есть
    } else {
        int parentIndex;
        printf("enter parent node index: ");
        scanf("%d", &parentIndex);
        Node **parentNode = FindNode(*root, parentIndex);

        if (parentNode == NULL || parentNode[1] == NULL) {
            printf("parent node not found\n");
            return;
        }

        Node *newChild = CreateNode(value);
        // если у родителя нет детей
        if (parentNode[1]->child == NULL) {
            parentNode[1]->child = newChild;
        } else { // если дети есть
            Node *temp = parentNode[1]->child;
            
            while (temp->sibling != NULL)
                temp = temp->sibling;
            temp->sibling = newChild;
        }
    }
}

void DeleteDescendants(Node **root) {
    if (*root == NULL)
        return;

    // делаем из ребёнка корень и всё удаляем
    Node *currentChild = *root;
    while (currentChild != NULL) {
        Node *temp = currentChild;
        currentChild = currentChild->sibling;
        DeleteDescendants(&(temp->child)); 
        printf("freeing node %d\n", temp->index);
        free(temp);
    }
}

void DeleteNode(Node **root, int index) {
    // нет корня
    if (*root == NULL) {
        printf("Root node not found\n");
        return;
    }

    // ищем корень
    Node **nodeToDelete = FindNode(*root, index);
    if (nodeToDelete == NULL || nodeToDelete[0] == NULL) {
        printf("Node with index %d not found\n", index);
        return;
    }

    // удаляем всех детей детей 
    DeleteDescendants(&(nodeToDelete[1]->child));
    
    // соединяет сиблинга с родителем
    if (nodeToDelete[0]->child == nodeToDelete[1]) {
        nodeToDelete[0]->child = nodeToDelete[1]->sibling;
    } else {
        Node *temp = nodeToDelete[0]->child;
        while (temp->sibling != nodeToDelete[1]) {
            temp = temp->sibling;
        }
        temp->sibling = nodeToDelete[1]->sibling;
    }

    printf("freeing node %d\n", nodeToDelete[1]->index);
    // удаляет сам узел
    free(nodeToDelete[1]);
    // чистит массив
    free(nodeToDelete);
}

void PrintTree(Node **root, int depth) {
    if (*root == NULL)
        return;

    Node *current = *root;

    for (int i = 0; i < depth; i++) {
        printf("\t");
    }
    printf("(%d) %d\n", current->index, current->value);

    PrintTree(&(current->child), depth + 1);
    PrintTree(&(current->sibling), depth);
}

int CountLeaves(Node *root) {
    if (root == NULL)
        return 0;

    if (root->child == NULL)
        return 1;

    int count = 0;
    Node *temp = root->child;
    while (temp != NULL) {
        count += CountLeaves(temp);
        temp = temp->sibling;
    }
    return count;
}

int main() {
    int choice, index;
    Node *root = NULL;

    while (1) {
        printf("1. add node\n");
        printf("2. delete node\n");
        printf("3. print tree\n");
        printf("4. count leaves\n");
        printf("5. exit\n");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                AddNode(&root);
                break;

            case 2:
                if (root == NULL) {
                    printf("root not found\n");
                } else {
                    printf("enter node index: ");
                    scanf("%d", &index);

                    if (root->index == index) {
                        DeleteDescendants(&root);
                        root = NULL;
                        break;
                    }
                    DeleteNode(&root, index);
                    
                    if (root == NULL) {
                        printf("root node deleted\n");
                    }
                }
                break;

            case 3:
                if (root == NULL) {
                    printf("root node not found\n");
                } else {
                    PrintTree(&root, 0);
                }
                break;

            case 4:
                if (root == NULL) {
                    printf("root node not found\n");
                } else {
                    printf("leaf count: %d\n", CountLeaves(root));
                }
                break;

            case 5:
                exit(0);

            default:
                printf("invalid choice\n");
        }
    }
    return 0;
}
