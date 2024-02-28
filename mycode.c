#include <stdio.h>
#include <stdlib.h>

typedef struct Node Node;

struct Node {
    Node* son;
    Node* bro;

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
    (*ptr)->bro = NULL;
    (*ptr)->son = NULL;
}

void Add(Node* parent, int val) {
    Node* ptr = (Node*)malloc(sizeof(Node));
    if (ptr == NULL) {
        printf("Узел не добавлен, недостаточно памяти\n");
        return;
    }

    if (parent->son == NULL) {
        parent->son = ptr;
    } else {
        Node* olderBro = parent->son;
        while (olderBro->bro != NULL) {
            olderBro = olderBro->bro;
        }
        olderBro->bro = ptr;
    }
    ptr->value = val;
    ptr->depth = parent->depth + 1;
    ptr->bro = NULL;
    ptr->son = NULL;
}

void Clear(Node** targ) {
    if ((*targ)->son != NULL) {
        Clear(&((*targ)->son));
    }
    if ((*targ)->bro != NULL) {
        Clear(&((*targ)->bro));
    }
    free(*targ);
    *targ = NULL;
}

void Del(Node** targ) {
    if ((*targ)->son != NULL) {
        Clear(&((*targ)->son));
    }

    Node* youngerBro = (*targ)->bro;
    free(*targ);
    *targ = youngerBro;
}

void PrintTree(Node* ptr) {
    for (int i = 0; i < ptr->depth; ++i) {
        printf("    ");
    }
    printf("%d\n", ptr->value);

    if (ptr->son != NULL) {
        PrintTree(ptr->son);
    }

    if (ptr->bro != NULL) {
        PrintTree(ptr->bro);
    }
}

int MyFunc(Node* parent) {
    int count = 0;
    int num = 0;
    Node* ptr = parent->son;
    while (ptr != NULL) {
        ++count;
        num += MyFunc(ptr);
        ptr = ptr->bro;
    }
    if (count == parent->value) {
        ++num;
    }
    return num;
}

void OnCheck(Node** tree) {
    printf("\n_____________________________________________\n\ni [value] - инициализация начального узла значением value\n\n");
    printf("a [value] [son number 1] ... [son number n] - добавить узел, родителем которого будет i-й сын j-го\n сына и тд. Индексация с нуля\n\n");
    printf("d [son number 1] ... [son number n] - удалить узел , выбор узла аналогичен добавлению\n\n");
    printf("f [val] - функция, согласно варианту\n\n");
    printf("p - вывести графическую визуализацию дерева\n\n");
    printf("s - очистка памяти и завершение работы программы\n\nПрошу не ставить лишние пробелы в конце строк\n_____________________________________________\n\n");
    
    char command = '0';
    char inp;
    printf("Инициализируйте первый узел:\n");

    while (command != 's') {
        
        command = getchar();

        if (*tree == NULL && command != 'i') {
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
                printf("Ура, можно работать\n");
                break;

            case 'a':
                getchar();
                Node* ptrA = *tree;
                int val;
                scanf("%d", &val);
                int targA = -1;
                    
                while (getchar() != '\n') {
                    scanf("%d", &targA);
                    
                    if (targA == -1) {
                        break;
                    }
                    ptrA = ptrA->son;
                    
                    for (int i = 0; i < targA; ++i) {
                        if (ptrA == NULL) {
                            break;
                        }
                        ptrA = ptrA->bro;
                    }
                    if (ptrA == NULL) {
                        break;
                    }
                }
                
                if (ptrA != NULL) {
                    Add(ptrA, val);
                    printf("Узел добавлен\n");
                } else {
                    printf("Не существует узла в этой позиции\n");
                    while (getchar() != '\n'){
                    continue;
                    }
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
                    ptrD = &((*ptrD)->son);
                    
                    for (int i = 0; i < targD; ++i) {
                        if (*ptrD == NULL) {
                            break;
                        }
                        ptrD = &((*ptrD)->bro);
                    }
                    if (*ptrD == NULL) {
                        break;
                    }
                }
                
                if (*ptrD != NULL) {
                    Del(ptrD);
                    printf("Узел удален\n");
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
                printf("Количество узлов, степень которых совпадает со значением: %d\n", MyFunc(*tree));
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