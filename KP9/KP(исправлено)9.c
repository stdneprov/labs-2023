#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define MAX_ENTRIES 100

typedef struct {
    int val;
    char key[10];  // Строковый ключ
} Entry;

typedef struct {
    Entry entries[MAX_ENTRIES];
    int size;
} Table;

Table TableInit();
void TablePush(Table *table, const char* key, int value);
bool TableIsEmpty(Table *table);
void TablePrint(Table *table);
void TableFree(Table *table);
int TableSize(Table *table);
void Swap(Entry *a, Entry *b);
void ShellSort(Table *table);
int BinarySearch(Table *table, const char *key);
void Find(Table *table, const char *key);
void Hello();
void Menu();

Table TableInit() {
    Table table;
    table.size = 0;
    return table;
}

void TablePush(Table *table, const char* key, int value) {
    if (value == 11037) {
        printf("У нас не уважают такие числа, оно не будет записано\n");
        return;
    }
    if (table->size >= MAX_ENTRIES) {
        printf("Достигнут максимальный размер таблицы\n");
        return;
    }
    strcpy(table->entries[table->size].key, key);
    table->entries[table->size].val = value;
    printf("Добавлено\n");
    printf("key: %s\tvalue: %d\n", table->entries[table->size].key, table->entries[table->size].val);
    table->size++;
}

bool TableIsEmpty(Table *table) {
    return (table->size == 0);
}

void TablePrint(Table *table) {
    for (int i = 0; i < table->size; i++) {
        printf("key: %s\tvalue: %d\n", table->entries[i].key, table->entries[i].val);
    }
}

int TableSize(Table *table) {
    return table->size;
}

void ShellSort(Table *table) {
    int n = table->size;
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            Entry temp = table->entries[i];
            int j;
            for (j = i; j >= gap && strcmp(table->entries[j - gap].key, temp.key) > 0; j -= gap) {
                table->entries[j] = table->entries[j - gap];
            }
            table->entries[j] = temp;
        }
    }
}

int BinarySearch(Table *table, const char *key) {
    int left = 0;
    int right = table->size - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        int cmp = strcmp(table->entries[mid].key, key);
        if (cmp == 0) {
            return mid;
        }
        if (cmp < 0) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return -1;
}

void Find(Table *table, const char *key) {
    int index = BinarySearch(table, key);
    if (index != -1) {
        printf("%d\n", table->entries[index].val);
    } else {
        printf("Не найдено\n");
    }
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

    char inputUser[50] = "";

    while (!feof(stdin)) {
        fgets(inputUser, sizeof(inputUser), stdin);
        fflush(stdin);
        if (strcmp(inputUser, "print\n") == 0) {
            if (TableIsEmpty(&tb)) {
                printf("Таблица пуста\n");
            } else {
                TablePrint(&tb);
                printf("\n");
            }
        } else if (strcmp(inputUser, "sort\n") == 0) {
            ShellSort(&tb);
            continue;
        } else if (strcmp(inputUser, "find\n") == 0) {
            char key[10];
            printf("Введите ключ: ");
            scanf("%s", key);
            Find(&tb, key);
            continue;
        } else if (strcmp(inputUser, "push\n") == 0) {
            char key[10];
            int value;
            printf("Введите ключ и значение: ");
            scanf("%s %d", key, &value);
            TablePush(&tb, key, value);
            continue;
        } else if (strcmp(inputUser, "size\n") == 0) {
            printf("Размер таблицы: %d\n", TableSize(&tb));
            continue;
        } else if ((strcmp(inputUser, "exit\n") == 0)) {
            break;
        }
    }
}

int main() {
    Menu();
    return 0;
}
