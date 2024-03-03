#include <stdio.h>
#include <stdlib.h>

typedef struct Node Node;

struct Node
{
    int id;
    Node *son;
    Node *bro;
    int value;
};

void FindNodeR(int id, Node* root, Node** res) {
    if ((root->son != NULL) && (root->son->id == id)) {
        res[0] = root->son;
        res[1] = root;
    } else if ((root->bro != NULL) && (root->bro->id == id)) {
        res[0] = root->bro;
        res[2] = root;
    } else {
        if (root->son != NULL) FindNodeR(id, root->son, res);
        if (root->bro != NULL) FindNodeR(id, root->bro, res);
    }
}

void FindNode(int id, Node* root, Node** res) {
    //0 - сам узел, 1 - отец если есть, 2 - старший брат если есть
    res[0] = NULL;
    res[1] = NULL;
    res[2] = NULL;
    if (root->id == id) {
        res[0] = root;
    } else {
        FindNodeR(id, root, res);
    }
}

void AddNode(int dad_id, int value, int *idCounter, Node* root) {
    Node *res[3]; // 0 - сам узел, 1 - отец если есть, 2 - старший брат если есть
    FindNode(dad_id, root, res);
    if (res[0] != NULL) {
        Node *dad = res[0];
        Node *newNode = (Node*)malloc(sizeof(Node));
        newNode->value = value;
        newNode->id = *idCounter;
        *idCounter = *idCounter + 1;
        newNode->bro = NULL;
        newNode->son = NULL;
        if (dad != NULL) {
            if (dad->son == NULL) {
                dad->son = newNode;
            } else {
                Node *oldBro = dad->son;
                while (oldBro->bro != NULL) {
                    oldBro = oldBro->bro;
                }
                oldBro->bro = newNode;
            }
        }
    }
}

void DelNodeR(Node *node) {
    if (node->son != NULL) {
        DelNodeR(node->son);
    }
    if (node->bro != NULL) {
        DelNodeR(node->bro);
    }
    free(node);
}

void DelNode(int id, Node *root) {
    Node *res[3]; // 0 - сам узел, 1 - отец если есть, 2 - старший брат если есть
    FindNode(id, root, res);
    if (res[1] != NULL) {
        res[1]->son = res[0]->bro;
    } else if (res[2] != NULL) {
        res[2]->bro = res[0]->bro;
    }
    if (res[0]->son != NULL) {
        DelNodeR(res[0]->son);
    }
    free(res[0]);
}

void ChangeValue(int id, int value, Node *root) {
    Node *res[3];
    FindNode(id, root, res);
    res[0]->value = value;
}

void PrintTree(Node *root, int depth) {
    for(int i = 0; i < depth; i++) {
        printf("   ");
    }
    printf("%d:%d\n", root->id, root->value);
    if (root->son != NULL) {
        PrintTree(root->son, depth + 1);
    }
    if (root->bro != NULL) {
        PrintTree(root->bro, depth);
    }
}

void PrintTreeD(Node *root) {
    printf("------------\n");
    PrintTree(root, 0);
    printf("------------\n");
}

void Width(Node* root, int depth, int** res, int* depthM) {
    if (depth >= *depthM) {
        *res = realloc(*res, 2 * sizeof(int) * *depthM);
        for (int i = *depthM; i < 2 * *depthM; i++) {
            (*res)[i] = 0;
        }
        *depthM = 2 * *depthM;
    }
    (*res)[depth] = (*res)[depth] + 1;
    if (root->bro != NULL) {
        Width(root->bro, depth, res, depthM);
    }
    if (root->son != NULL) {
        Width(root->son, depth + 1, res, depthM);
    }
}

void PrintWidth(int* res, int depthM) {
    int m = 0;
    for (int i = 0; i < depthM; i++) {
        if (res[i] > m) {
            m = res[i];
        }
    }
    printf("width = %d\n", m);
}

int main() {
    int idCounter = 1;
    Node *root =  (Node*)malloc(sizeof(Node));
    root->bro = NULL;
    root->son = NULL;
    root->id = 0;
    root->value = 0;
    char command;
    int arg1, arg2;
    printf("a x1 x2: add node, x1 - dad's id, x2 - value\n");
    printf("d x1: del node, x1 - id\n");
    printf("c x1 x2: change value, x1 - id, x2 - new value\n");
    printf("f: width of tree\n");
    printf("p: print tree\n");
    printf("s: stop\n");
    printf("node 1:2 means id = 1, value = 2\n");
    PrintTreeD(root);
    do {
        scanf("%c", &command);
        if (command == 'a') {
            scanf("%d %d", &arg1, &arg2);
            AddNode(arg1, arg2, &idCounter, root);
            PrintTreeD(root);
        } else if (command == 'd') {
            scanf("%d", &arg1);
            DelNode(arg1, root);
            PrintTreeD(root);
        } else if (command == 'c') {
            scanf("%d %d", &arg1, &arg2);
            ChangeValue(arg1, arg2, root);
            PrintTreeD(root);
        } else if (command == 'p') {
            PrintTreeD(root);
        } else if (command == 'f') {
            int depthM = 2;
            int *res = (int*)malloc(sizeof(int) * depthM);
            for (int i = 0; i < depthM; i++) {
                res[i] = 0;
            }
            Width(root, 0, &res, &depthM);
            printf("------------\n");
            PrintWidth(res, depthM);
            printf("------------\n");
        }
    } while (command != 's');
    return 0;
}