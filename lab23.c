#include <stdio.h>
#include <stdlib.h>

typedef struct Node Node;
int idCounter = 0;
int countNodesWithTwoSubtrees = 0;

struct Node {
    int value;
    int id;
    Node* son;
    Node* bro;
};

void GetInfo() {
    printf(
        "\n"
        "i - создание первого узла\n"
        "a - добавление нового узла\n"
        "d - удаление узла\n"
        "p - текстовая визуализация дерева\n"
        "f - вывести число вершин с двумя поддеревьями\n"
        "e - выход\n");
}

void InitTree(Node** tree, int value) {
    if (*tree != NULL) {
        printf("Начальный узел уже существует\n");
        return;
    }
    *tree = (Node*)malloc(sizeof(Node));
    (*tree)->value = value;
    (*tree)->bro = NULL;
    (*tree)->son = NULL;
    (*tree)->id = ++idCounter;
    printf("Успешно, id = %d\n", (*tree)->id);
}

void InfoNode(Node* curNodeOriginal) {
    Node* curNode = curNodeOriginal;
    printf("Сейчас вы находитесь в узле с id = %d, value = %d\n", curNode->id, curNode->value);
    Node* son = curNode->son;
    if (!son) {
        printf("Сыновей нет\n");
        return;
    }
    printf("Можете перейти к следующим узлам:\n"
        "id    value\n");
    while (son) {
        printf("%d    %d\n", son->id, son->value);
        son = son->bro;
    }
}

void InfoNodeForDelete(Node** curNodeOriginal) {
    Node* curNode = *curNodeOriginal;
    printf("Сейчас вы находитесь в узле с id = %d, value = %d\n", curNode->id, curNode->value);
    Node* son = curNode->son;
    if (!son) {
        printf("Сыновей нет\n");
        return;
    }
    printf("Можете перейти к следующим узлам:\n"
        "id    value\n");
    while (son) {
        printf("%d    %d\n", son->id, son->value);
        son = son->bro;
    }
}

void Clear(Node** targ) {
    if ((*targ)->son != NULL) {
        Clear(&((*targ)->son));
    }
    Node* ptr = (*targ)->bro;
    free(*targ);
    *targ = ptr;
}

Node* SearchNode(Node* curNode, int id) {
    Node* son = curNode->son;
    if (!son) {
        printf("Сыновей нет\n");
        return curNode;
    }
    while (son->id != id) {
        if (son->bro) {
            son = son->bro;
        }
        else {
            printf("Узел не найден\n");
            return curNode;
        }
    }
    return son;
}

Node** SearchNodeForDelete(Node** curNode, int id) {
    Node** son = &(*curNode)->son;
    if (!(*son)) {
        printf("Сыновей нет\n");
        return curNode;
    }
    while ((*son)->id != id) {
        if ((*son)->bro) {
            son = &(*son)->bro;
        }
        else {
            printf("Узел не найден\n");
            return curNode;
        }
    }

    return son;
}

Node* CreateNode() {
    Node* nodeAns = (Node*)malloc(sizeof(Node));
    nodeAns->value = 0;
    nodeAns->bro = NULL;
    nodeAns->son = NULL;
    nodeAns->id = ++idCounter;
    return nodeAns;
}

Node* GetYoungerSon(Node* parent) {
    Node* son = parent->son;
    while (son->bro) {
        son = son->bro;
    }

    return son;
}

void AddSon(Node* parent, int value) {
    Node* node = CreateNode();
    node->value = value;
    if (parent->son) {
        GetYoungerSon(parent)->bro = node;
    }
    else {
        parent->son = node;
    }
}

void AddNote(Node* nodeOriginal) {
    Node* curNode = nodeOriginal;
    printf(
        "Добавление происходит в интерактивном режиме\n"
        "Чтобы перейти к узлу из списка ниже введите 1\n"
        "Чтобы добавить сына к текущему узлу введите 2\n"
        "Чтобы выйти введите 3\n\n"
    );
    int cmd = 0;
    while (cmd != 3) {
        InfoNode(curNode);
        scanf("%d", &cmd);
        switch (cmd) {
        case 2:
            printf("Введите значение узла\n");
            int newNodeValue;
            scanf("%d", &newNodeValue);
            AddSon(curNode, newNodeValue);
            break;
        case 1:
            printf("Введите id узла\n");
            int nodeId;
            scanf("%d", &nodeId);
            curNode = SearchNode(curNode, nodeId);
            break;
        default:
            printf("Неизвестная команда\n");
            break;
        }
    }
}

void DelNote(Node** curNote) {
    printf(
        "\nУдаление происходит в интерактивном режиме\n"
        "Чтобы перейти к узлу из списка ниже введите 1\n"
        "Чтобы удалить текущий узел 2\n"
        "Чтобы выйти введите 3\n\n"
    );
    int cmd = 0;
    while (cmd != 3) {
        InfoNodeForDelete(curNote);
        scanf("%d", &cmd);
        switch (cmd) {
        case 2:
            Clear(curNote);
            return;
        case 1:
            printf("Введите id узла\n");
            int nodeId;
            scanf("%d", &nodeId);
            curNote = SearchNodeForDelete(curNote, nodeId);
            break;
        default:
            printf("Неизвестная команда\n");
            break;
        }
    }
}

void PrintTree(Node* ptr, int deep) {
    for (int i = 0; i < deep; ++i) {
        printf("\t");
    }
    printf("%d\n", ptr->value);

    if (ptr->son != NULL) {
        PrintTree(ptr->son, deep + 1);
    }

    if (ptr->bro != NULL) {
        PrintTree(ptr->bro, deep);
    }
}

void CountNodesWithTwoSubtrees(Node* ptr) {
    int sonCount = 0;
    Node* son = ptr->son;
    while (son != NULL) {
        sonCount++;
        son = son->bro;
    }
    if (sonCount == 2) {
        countNodesWithTwoSubtrees++;
    }

    if (ptr->son != NULL) {
        CountNodesWithTwoSubtrees(ptr->son);
    }
    if (ptr->bro != NULL) {
        CountNodesWithTwoSubtrees(ptr->bro);
    }
}

void Start(Node** tree) {
    GetInfo();
    while (1) {
        char cmd = getchar();
        if (cmd == '\n' || cmd == ' ') {
            continue;
        }
        if (cmd != 'i' && *tree == NULL) {
            printf("Инициализируйте первый узел\n");
            continue;
        }
        switch (cmd) {
        case 'i':
            printf("Введите значение первого узла\n");
            int valueI;
            scanf("%d", &valueI);
            InitTree(tree, valueI);
            break;
        case 'a':
            AddNote(*tree);
            break;
        case 'd':
            DelNote(tree);
            break;
        case 'p':
            PrintTree(*tree, 0);
            break;
        case 'f':
            countNodesWithTwoSubtrees = 0;
            CountNodesWithTwoSubtrees(*tree);
            printf("Число вершин с двумя поддеревьями равно %d\n", countNodesWithTwoSubtrees);
            break;
        case 'e':
            Clear(tree);
            return;
        default:
            printf("Неизвестная команда %c \n", cmd);
            break;
        }
        GetInfo();
    }
}

int main() {
    Node* tree = NULL;
    Start(&tree);
    return 0;
}
