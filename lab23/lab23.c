#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int index;
    int value;
    struct Node *child;
    struct Node *sibling;
} Node;

int currentIndex = 1;

Node* CreateNode(int value) {
    Node *newNode = (Node*)malloc(sizeof(Node));

    newNode->index = currentIndex++;
    newNode->value = value;
    newNode->child = NULL;
    newNode->sibling = NULL;
    return newNode;
}

Node* FindNode(Node *root, int index) {
    if (root == NULL)
        return NULL;
    
    if (root->index == index)
        return root;

    Node *temp = FindNode(root->child, index);
    if (temp != NULL)
        return temp;
    
    return FindNode(root->sibling, index);
}

void AddNode(Node **root) {
    int value;
    printf("enter new node value: ");
    scanf("%d", &value);
    
    if (*root == NULL) {
        *root = CreateNode(value);
    } else {
        int parentIndex;
        printf("enter parent node index: "); 
        scanf("%d", &parentIndex); 

        Node *parentNode = FindNode(*root, parentIndex);
        if (parentNode == NULL) {
            printf("parent node not found\n");
            return;
        }

        Node *newChild = CreateNode(value);

        // вставляем ребёнка родителю
        if (parentNode->child == NULL) {
            parentNode->child = newChild;
        } else {
            Node *temp = parentNode->child;
            
            // либо вставляем его сиблингом
            while (temp->sibling != NULL)
                temp = temp->sibling;
            temp->sibling = newChild;
        }
    }
}

void DeleteNode(Node **root, int index) {
    if (*root == NULL)
        return;

    // если надо удалить корень
    if ((*root)->index == index) {
        Node *temp = *root;
        *root = (*root)->sibling;
        free(temp);
        return;
    }
    
    // удалить ребёнка и переместить сиблинга вверх
    if ((*root)->child != NULL && (*root)->child->index == index) {
        Node *temp = (*root)->child;
        (*root)->child = temp->sibling;
        free(temp);
        return;
    }

    // если надо копаться в детях
    Node *prev = (*root)->child;
    Node *current = prev->sibling;

    while (current != NULL) {
        if (current->index == index) {
            prev->sibling = current->sibling;
            free(current);
            return;
        }
        prev = current;
        current = current->sibling;
    }

    DeleteNode(&((*root)->child), index);
    DeleteNode(&((*root)->sibling), index);
}

void PrintTree(Node *root, int depth) {
    if (root == NULL)
        return;

    for (int i = 0; i < depth; i++)
        printf("\t");
    printf("(%d) %d\n", root->index, root->value);

    PrintTree(root->child, depth + 1);
    PrintTree(root->sibling, depth);
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
        printf("1. add Node\n");
        printf("2. delete Node\n");
        printf("3. show tree\n");
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
                    DeleteNode(&root, index);
                }
                break;

            case 3:
                if (root == NULL) {
                    printf("tree is empty\n");
                } else {
                    PrintTree(root, 0);
                }
                break;

            case 4:
                if (root == NULL) {
                    printf("root not found\n");
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
