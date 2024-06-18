#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct Table {
    int val;
    char key[10];  // Строковый ключ
    struct Table *last;
    struct Table *next;
    int size;
} Table;

Table TableInit();
void TablePush(Table *table, const char* key, int value);
bool TableIsEmpty(Table *table);
void TablePrint(Table *table);
void TableFree(Table *table);
int TableSize(Table *table);
void Swap(Table *a, Table *b);
void ShellSort(Table *head);

Table TableInit() {
    Table new;
    new.size = 0;
    new.last = NULL;
    new.next = NULL;
    return new;
}

void TablePush(Table *table, const char* key, int value) {
    if (value == 11037) {
        printf("У нас не уважают такие числа, оно не будет записано");
        exit(-1);
    }
    if (table->size == 0) {
        table->next = NULL;
        strcpy(table->key, key);  // Копирование строки
        table->val = value;
        table->last = table;
    } else {
        Table* new = (Table *)malloc(sizeof(Table));
        if (new == NULL) {
            exit(-1);
        }
        strcpy(new->key, key);  // Копирование строки
        new->val = value;
        table->last->next = new;
        new->next = NULL;
        table->last = new;
    }
    printf("Добавлено\n");
    printf("key: %s\tvalue: %d\n", table->last->key, table->last->val);
    table->size++;
}

bool TableIsEmpty(Table *table) {
    return (table->size == 0);
}

void TablePrint(Table *table) {
    Table *current = table;
    while (current != NULL) {
        printf("key: %s\tvalue: %d\n", current->key, current->val);
        current = current->next;
    }
}

void TableFree(Table *table) {
    Table *next;
    for (Table *i = table; i != NULL; i = next) {
        next = i->next;
        free(i);
    }
}

int TableSize(Table *table) {
    return table->size;
}

void Swap(Table *a, Table *b) {
    int temp_val = a->val;
    char temp_key[10];
    strcpy(temp_key, a->key);
    a->val = b->val;
    strcpy(a->key, b->key);
    b->val = temp_val;
    strcpy(b->key, temp_key);
}

void ShellSort(Table *head) {
    if (head == NULL || head->next == NULL) {
        return;
    }

    int n = TableSize(head);
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (Table *i = head; i != NULL; i = i->next) {
            Table *j = i;
            for (int k = 0; k < gap && j != NULL; k++) {
                j = j->next;
            }
            while (j != NULL) {
                if (strcmp(i->key, j->key) > 0) {
                    Swap(i, j);
                }
                j = j->next;
                for (int k = 0; k < gap - 1 && j != NULL; k++) {
                    j = j->next;
                }
            }
        }
    }
}

void Find(Table *table, const char *a) {
    while (table != NULL) {
        if (strcmp(table->key, a) == 0) {
            printf("%d\n", table->val);
            return;
        }
        table = table->next;
    }
    printf("NE Naideno\n");
    return;
}

void Hello() {
    printf("Это меню управления программой\n");
    printf("Если хочешь добавить значение - введи push и в следующей строке ключ и значение\n");
    printf("Если хочешь отсортировать - введи sort\n");
    printf("Если хочешь посмотреть таблицу - введи print\n");
    printf("Если хочешь узнать размер - введи size\n");
    printf("Если хочешь узнать элемент по ключу - введи find и в следующей строчке ключ\n");
    printf("Если хочешь удалить значение - введи pop и в следующей строке ключ\n");
    printf("Если хочешь выйти - введи exit или ctrl+D\n");
    printf("В случае неверной команды ничего не произойдет\n");
}

void Menu() {
    Hello();
    Table tb = TableInit();

    char inputUser[10] = "";

    while (!feof(stdin)) {
        fgets(inputUser, sizeof(inputUser), stdin);
        fflush(stdin);
        if (strcmp(inputUser, "print\n") == 0) {
            if (TableIsEmpty(&tb)) {
                printf("словарь не задан\n");
            } else {
                TablePrint(&tb);
                printf("\n");
            }
        } else if (strcmp(inputUser, "sort\n") == 0) {
            ShellSort(&tb);
            continue;
        } else if (strcmp(inputUser, "find\n") == 0) {
            char key[100];
            scanf("%s", key);
            Find(&tb, key);
            continue;
        } else if (strcmp(inputUser, "push\n") == 0) {
            char key[100];
            int value;
            scanf("%s %d", key, &value);
            TablePush(&tb, key, value);
            continue;
        } else if (strcmp(inputUser, "size\n") == 0) {
            printf("%d\n", TableSize(&tb));
            continue;
        } else if ((strcmp(inputUser, "exit\n") == 0)) {
            break;
        }
    }

    TableFree(&tb);
}

int main() {
    Menu();
    return 0;
}
