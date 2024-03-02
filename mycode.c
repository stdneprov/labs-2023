#include <stdio.h>
#include <stdlib.h>

typedef struct Node Node;

struct Node {
    Node* left;
    Node* right;

    int value;
    int depth;
};

void Init(Node** ptr, int val) {
    if (*ptr != NULL) {
        printf("Ошибка инициализации, дерево уже существует\n");
        return;
    }
    *ptr = (Node*)malloc(sizeof(Node));
    if (*ptr == NULL) {
        printf("Ошибка инициализации, недостаточно памяти\n");
        return;
    }
    (*ptr)->value = val;
    (*ptr)->depth = 0;
    (*ptr)->left = NULL;
    (*ptr)->right = NULL;
    printf("Ура, можно работать\n");
}

int Add(Node** parent, int val) {
    Node* ptr = (Node*)malloc(sizeof(Node));
    int d = 0;
    if (ptr == NULL) {
        printf("Узел не добавлен, недостаточно памяти\n");
        return 0;
    }

    while (*parent != NULL) {
        if (val > (*parent)->value) {
            parent = &((*parent)->right);
            ++d;
        } else if (val < (*parent)->value) {
            parent = &((*parent)->left);
            ++d;
        } else {
            printf("Узел с таким значением уже существует\n");
            return 0;
        }
    } 
    *parent = ptr;
    ptr->value = val;
    ptr->depth = d;
    ptr->left = NULL;
    ptr->right = NULL;
    return 1;
}

void Move(Node* targ) {
    if (targ == NULL) {
        return;
    }
    Move(targ->left);
    Move(targ->right);
    --(targ->depth);
}

void Del(Node** targ) {
    Node** ptr;
    Node* new;

    if ((*targ)->right != NULL) {
        ptr = &((*targ)->right);
        while ((*ptr)->left != NULL) {
            ptr = &(*ptr)->left;
        }
        new = *ptr;

        if ((*ptr)->right != NULL) {
            *ptr = (*ptr)->right;
            Move(*ptr);
        } else {
            *ptr = NULL;
        }

        new->right = (*targ)->right;
        new->left = (*targ)->left;
        new->depth = (*targ)->depth;

        free(*targ);
        *targ = new;

    } else if ((*targ)->left != NULL) {
        ptr = &((*targ)->left);
        while ((*ptr)->right != NULL) {
            ptr = &(*ptr)->right;
        }
        new = *ptr;

        if ((*ptr)->left != NULL) {
            *ptr = (*ptr)->left;
            Move(*ptr);
        } else {
            *ptr = NULL;
        }

        new->left = (*targ)->left;
        new->right = (*targ)->right;
        new->depth = (*targ)->depth;

        free(*targ);
        *targ = new;

    } else {
        free(*targ);
        *targ = NULL;
    }
}

void Clear(Node** tree) {
    if (*tree == NULL) {
        return;
    }
    Clear(&((*tree)->left));
    Clear(&((*tree)->right));
    free(*tree);
    *tree = NULL;
}

void PrintTree(Node* ptr) {
    for (int i = 0; i < ptr->depth; ++i) {
        printf("    ");
    }
    printf("%d\n", ptr->value);

    if (ptr->right != NULL) {
        PrintTree(ptr->right);
    }

    if (ptr->left != NULL) {
        PrintTree(ptr->left);
    }
}

int _myFunc(Node* tree, int* d, int* v) {
    if (tree == NULL) {
        return 0;

    } else if ((tree->right != NULL) || (tree->left != NULL)) {

        _myFunc(tree->left, d, v);
        _myFunc(tree->right, d, v);
        if (tree->depth > *d) {
            *d = tree->depth;
            *v = tree->value;
        }
        return 1;
    } else {
        return 0;
    }
}

void MyFunc(Node* tree) {
    int d = tree->depth;
    int v = tree->value;
    if (_myFunc(tree, &d, &v)) {
        printf("Значение самой глубокой нетерминальной вершины: %d\n", v);
    } else {
        printf("Нетерминальной вершины не существует\n");
    }
}

void OnCheck(Node** tree) {
    printf("\n_____________________________________________\n\ni [value] - инициализация начального узла значением value\n\n");
    printf("a [value] - добавить узел\n\n");
    printf("d [0..1] ... [0..1] - удалить узел, 0 - левый сын, 1 - правый. Отсутствие параметров - удаление\n первого узла\n\n");
    printf("f - функция, согласно варианту\n\n");
    printf("p - вывести графическую визуализацию дерева\n\n");
    printf("s - очистка памяти и завершение работы программы\n\nПрошу не ставить лишние пробелы в конце строк\n_____________________________________________\n\n");
    
    char command = '0';
    char inp;
    printf("Инициализируйте первый узел:\n");

    while (command != 's') {
        
        command = getchar();

        if (*tree == NULL && (command != 'i' && command != 's')) {
            printf("Ты тупой или чё?\n");
            while (getchar() != '\n'){
                continue;
            }
            continue;
        }

        switch (command) {
            case 'i':
                getchar();
                int in;
                scanf("%d", &in);
                Init(tree, in);
                while (getchar() != '\n'){
                    continue;
                }
                break;

            case 'a':
                getchar();
                int val;
                scanf("%d", &val);
                
                if (Add(tree, val)) {
                    printf("Узел добавлен\n");
                }
                
                while (getchar() != '\n'){
                    continue;
                }
                
                break;

            case 'd':
                Node** ptrD = tree;
                int targD = -1;
                
                while (getchar() != '\n') {
                    scanf("%d", &targD);
                    
                    if (targD == -1) {
                        break;
                    }

                    if (targD == 1) {
                        ptrD = &((*ptrD)->right);
                    } else if (targD == 0) {
                        ptrD = &((*ptrD)->left);
                    }
        
                    if (*ptrD == NULL) {
                        break;
                    }
                }
                
                if (*ptrD != NULL) {
                    Del(ptrD);
                    printf("Узел удален\n");
                    if (*tree == NULL) {
                        command = 's';
                        printf("Я тебе больше не нужен? Ну лан... Тогда сдохну :(\n");
                    }
                } else {
                    printf("Не существует узла в этой позиции\n");
                    while (getchar() != '\n'){
                        continue;
                    }
                }
                break;
            
            case 'f':
                while (getchar() != '\n'){
                    continue;
                }
                MyFunc(*tree);
                break;
            
            case 'p':
                while (getchar() != '\n'){
                    continue;
                }
                printf("Ща нарисуем\n");
                PrintTree(*tree);
                break;

            case 's':
                while (getchar() != '\n'){
                    continue;
                }
                if (*tree != NULL) {
                    Clear(tree);
                } else {
                    printf("Ну ок\n");
                    break;
                }
                printf("Я тебе больше не нужен? Ну лан... Тогда сдохну :(\n");
                break;
            
            default:
                while (getchar() != '\n'){
                    continue;
                }
                printf("Я тебя не понял, попробуй ещё раз\n");
                break;
        }
    } 
}

int main() {
    Node* tree = NULL;
    
    OnCheck(&tree);

    return 0;
}