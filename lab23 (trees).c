#include <stdio.h> // Подключение стандартной библиотеки ввода-вывода
#include <stdlib.h> // Подключение стандартной библиотеки для работы с памятью

// Определение типа Node, представляющего узел дерева
typedef struct Node Node;

// Инициализация счетчика id для узлов
int idCounter = 0;

// Структура узла дерева
struct Node {
    int value; // Значение узла
    int id;     // Идентификатор узла
    Node *son; // Указатель на сына узла
    Node *brother; // Указатель на брата узла
};

// Функция для вывода информации о доступных командах
void GetInfo() {
    printf(
            "\n"
            "i - создание первого узла\n"
            "a - добавление нового узла\n"
            "d - удаление узла\n"
            "g - текстовая визуализация дерева\n"
            "c - подсчет количества вершин\n" // Добавили команду "c"
            "e - выход\n");
}

// Функция для инициализации дерева
void InitTree(Node **tree, int value) {
    // Проверка, существует ли уже корневой узел
    if (*tree != NULL) {
        printf("Начальный узел уже существует\n");
        return;
    }

    // Выделение памяти для нового узла
    *tree = (Node *) malloc(sizeof(Node));

    // Инициализация значений нового узла
    (*tree)->value = value;
    (*tree)->brother = NULL;
    (*tree)->son = NULL;
    (*tree)->id = ++idCounter; // Увеличение счетчика id
    printf("Успешно, id = %d\n", (*tree)->id);
}

// Функция для вывода информации о текущем узле
void InfoNode(Node *curNodeOriginal) {
    Node* curNode = curNodeOriginal;
    printf("Сейчас вы находитесь в узле с id = %d, value = %d\n", curNode->id, curNode->value);
    Node *son = curNode->son;
    if (!son) {
        printf("Сыновей нет\n");
        return;
    }
    printf("Можете перейти к следующим узлам:\n"
           "id    value\n");
    while (son) {
        printf("%d    %d\n", son->id, son->value);
        son = son->brother;
    }
}

// Функция для вывода информации о текущем узле (для удаления)
void InfoNodeForDelete(Node** curNodeOriginal) {
    Node* curNode = *curNodeOriginal;
    printf("Сейчас вы находитесь в узле с id = %d, value = %d\n", curNode->id, curNode->value);
    Node *son = curNode->son;
    if (!son) {
        printf("Сыновей нет\n");
        return;
    }
    printf("Можете перейти к следующим узлам:\n"
           "id    value\n");
    while (son) {
        printf("%d    %d\n", son->id, son->value);
        son = son->brother;
    }
}

// Функция для очистки дерева
void Clear(Node** targ) {
    // Рекурсивно очищаем поддерево
    if ((*targ)->son != NULL) {
        Clear(&((*targ)->son));
    }

    // Удаляем текущий узел
    Node* ptr = (*targ)->brother;
    free(*targ);
    *targ=ptr;
}

// Функция для поиска узла по id
Node *SearchNode(Node *curNode, int id) {
    Node *son = curNode->son;
    if (!son) {
        printf("Сыновей нет\n");
        return curNode;
    }
    while (son->id != id) {
        if (son->brother) {
            son = son->brother;
        } else {
            printf("Узел не найден\n");
            return curNode;
        }
    }
    return son;
}

// Функция для поиска узла по id (для удаления)
Node** SearchNodeForDelete(Node** curNode, int id) {
    Node** son = &(*curNode)->son;
    if (!(*son)) {
        printf("Сыновей нет\n");
        return curNode;
    }
    while ((*son)->id != id) {
        if ((*son)->brother) {
            son = &(*son)->brother;
        } else {
            printf("Узел не найден\n");
            return curNode;
        }
    }

    return son;
}

// Функция для создания нового узла
Node *CreateNode() {
    Node *nodeAns = (Node *) malloc(sizeof(Node));
    nodeAns->value = 0;
    nodeAns->brother = NULL;
    nodeAns->son = NULL;
    nodeAns->id = ++idCounter;
    return nodeAns;
}

// Функция для получения самого младшего сына
Node* GetYoungerSon(Node *parent) {
    Node *son = parent->son;
    while (son->brother) {
        son = son->brother;
    }

    return son;
}

// Функция для добавления сына к узлу
void AddSon(Node *parent, int value) {
    // Создание нового узла
    Node* node = CreateNode();
    node->value = value;

    // Добавление нового узла в список братьев
    if (parent->son) {
        GetYoungerSon(parent)->brother=node;
    } else {
        parent->son = node;
    }
}

// Функция для добавления узла в интерактивном режиме
void AddNote(Node *nodeOriginal) {
    Node* curNode = nodeOriginal;
    printf(
            "Добавление происходит в интерактивном режиме\n"
            "Чтобы добавить сына к текущему узлу введите 1\n"
            "Чтобы перейти к узлу из списка ниже введите 2\n"
            "Чтобы выйти введите 3\n\n"
    );
    int cmd = 0;
    while (cmd != 3) {
        InfoNode(curNode);
        scanf("%d", &cmd);
        switch (cmd) {
            case 1:
                printf("Введите значение узла\n");
                int newNodeValue;
                scanf("%d", &newNodeValue);
                AddSon(curNode, newNodeValue);
                break;
            case 2:
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

// Функция для удаления узла в интерактивном режиме
void DelNote(Node** curNote) {
    printf(
            "\nУдаление происходит в интерактивном режиме\n"
            "Чтобы удалить текущий узел 1\n"
            "Чтобы перейти к узлу из списка ниже введите 2\n"
            "Чтобы выйти введите 3\n\n"
    );
    int cmd = 0;
    while (cmd != 3) {
        InfoNodeForDelete(curNote);
        scanf("%d", &cmd);
        switch (cmd) {
            case 1:
                Clear(curNote);
                return;
            case 2:
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

// Функция для вывода дерева в текстовом виде
void PrintTree(Node* ptr, int deep) {
    // Вывод отступов для визуального представления структуры дерева
    for (int i = 0; i < deep; ++i) {
        printf("\t");}
    printf("%d\n", ptr->value);

    // Рекурсивный вызов для сына
    if (ptr->son != NULL) {
        PrintTree(ptr->son, deep + 1);
    }

    // Рекурсивный вызов для брата
    if (ptr->brother != NULL) {
        PrintTree(ptr->brother, deep);
    }
}

// Функция для подсчета количества вершин в дереве
int CountNodes(Node* ptr) {
    // Базовый случай: если узел пуст, количество вершин равно 0
    if (ptr == NULL) {
        return 0;
    }

    // Инициализация счетчика количеством 1 (текущий узел)
    int count = 1;

    // Рекурсивный подсчет вершин в левом поддереве
    if (ptr->son != NULL) {
        count += CountNodes(ptr->son);
    }

    // Рекурсивный подсчет вершин в правом поддереве
    if (ptr->brother != NULL) {
        count += CountNodes(ptr->brother);
    }

    // Возвращение суммарного количества вершин
    return count;
}

// Функция для запуска программы
void Start(Node **tree) {
    GetInfo(); // Вывод информации о командах
    while (1) {
        char cmd = getchar();
        // Игнорирование пустых символов
        if (cmd == '\n' || cmd == ' ') {
            continue;
        }

        // Проверка на инициализацию первого узла
        if (cmd != 'i' && *tree == NULL) {
            printf("Инициализируйте первый узел\n");
            continue;
        }

        // Обработка команд
        switch (cmd) {
            case 'i':
                printf("Введите значение первого узла\n");
                int valueI;
                scanf("%d", &valueI);
                InitTree(tree, valueI); // Инициализация дерева
                break;
            case 'a':
                AddNote(*tree); // Добавление узла в интерактивном режиме
                break;
            case 'd':
                DelNote(tree); // Удаление узла в интерактивном режиме
                break;
            case 'g':
                PrintTree(*tree, 0); // Вывод дерева
                break;
            case 'c': // Команда для подсчета вершин
                if (*tree == NULL) {
                    printf("Дерево пусто\n");
                } else {
                    printf("Количество вершин в дереве: %d\n", CountNodes(*tree));
                }
                break;
            case 'e':
                Clear(tree); // Очистка дерева
                return;
            default:
                printf("Неизвестная команда %c \n", cmd);
                break;
        }
        GetInfo(); // Вывод информации о командах
    }
}

int main() {
    Node *tree = NULL;
    Start(&tree); // Запуск программы
    return 0;
}
