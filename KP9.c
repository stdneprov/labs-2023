#define _CRT_SECURE_NO_WARNINGS
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_ENTRIES 100
#define MIN_ENTRIES 3

typedef struct {
    char key[7];
    char text[100];
} Entry;

typedef struct {
    Entry entries[MAX_ENTRIES];
    int size;
} Table;

Table TableInit() {
    Table table;
    table.size = 0;
    return table;
}

void TablePush(Table* table, const char* key, const char* text) {
    if (table->size >= MAX_ENTRIES) {
        printf("Достигнут максимальный размер таблицы\n");
        return;
    }
    strcpy(table->entries[table->size].key, key);
    strcpy(table->entries[table->size].text, text);
    table->size++;
}

void TablePop(Table* table, const char* key) {
    int index = -1;
    for (int i = 0; i < table->size; i++) {
        if (strcmp(table->entries[i].key, key) == 0) {
            index = i;
            break;
        }
    }
    if (index != -1) {
        for (int i = index; i < table->size - 1; i++) {
            table->entries[i] = table->entries[i + 1];
        }
        table->size--;
    }
    else {
        printf("Элемент с ключом %s не найден\n", key);
    }
}

void TablePrint(Table* table) {
    for (int i = 0; i < table->size; i++) {
        printf("key: %s\ttext: %s\n", table->entries[i].key, table->entries[i].text);
    }
}

void Merge(Table* table, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    Entry* L = (Entry*)malloc(n1 * sizeof(Entry));
    Entry* R = (Entry*)malloc(n2 * sizeof(Entry));

    for (int i = 0; i < n1; i++)
        L[i] = table->entries[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = table->entries[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (strcmp(L[i].key, R[j].key) <= 0) {
            table->entries[k] = L[i];
            i++;
        }
        else {
            table->entries[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        table->entries[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        table->entries[k] = R[j];
        j++;
        k++;
    }

    free(L);
    free(R);
}

void MergeSort(Table* table, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        MergeSort(table, left, mid);
        MergeSort(table, mid + 1, right);

        Merge(table, left, mid, right);
    }
}

int BinarySearch(Table* table, const char* key) {
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
        }
        else {
            right = mid - 1;
        }
    }
    return -1;
}

void FillTableToMinSize(Table* table) {
    while (table->size < MIN_ENTRIES) {
        char key[7];
        char text[100];
        printf("Введите ключ (макс 6 символов): ");
        scanf("%6s", key);
        getchar();
        printf("Введите текст: ");
        fgets(text, sizeof(text), stdin);
        text[strcspn(text, "\n")] = 0;
        TablePush(table, key, text);
    }
}

void Menu() {
    Table tb = TableInit();

    printf("Инициализация таблицы. Минимальное количество записей: %d.\n", MIN_ENTRIES);
    FillTableToMinSize(&tb);

    while (1) {
        printf("\nМеню:\n");
        printf("1. Добавить запись\n");
        printf("2. Удалить запись\n");
        printf("3. Сортировать таблицу (двухпоточное слияние)\n");
        printf("4. Печать таблицы\n");
        printf("5. Найти элемент по ключу (двоичный поиск)\n");
        printf("6. Выйти\n");

        int choice;
        printf("Ваш выбор: ");
        scanf("%d", &choice);
        getchar();

        if (choice == 1) {
            char key[7];
            char text[100];
            printf("Введите ключ (макс 6 символов): ");
            scanf("%6s", key);
            getchar();
            printf("Введите текст: ");
            fgets(text, sizeof(text), stdin);
            text[strcspn(text, "\n")] = 0;
            TablePush(&tb, key, text);
        }
        else if (choice == 2) {
            char key[7];
            printf("Введите ключ для удаления: ");
            scanf("%6s", key);
            TablePop(&tb, key);
            if (tb.size < MIN_ENTRIES) {
                printf("Таблица содержит меньше минимального количества записей(Добавьте запись).\n");
                FillTableToMinSize(&tb);
            }
        }
        else if (choice == 3) {
            MergeSort(&tb, 0, tb.size - 1);
            printf("Таблица отсортирована\n");
        }
        else if (choice == 4) {
            TablePrint(&tb);
        }
        else if (choice == 5) {
            char key[7];
            printf("Введите ключ для поиска: ");
            scanf("%6s", key);
            int index = BinarySearch(&tb, key);
            if (index != -1) {
                printf("Найден элемент: key: %s\ttext: %s\n", tb.entries[index].key, tb.entries[index].text);
            }
            else {
                printf("Элемент с ключом %s не найден\n", key);
            }
        }
        else if (choice == 6) {
            break;
        }
        else {
            printf("Неверный выбор. Попробуйте снова.\n");
        }
    }
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    Menu();
    return 0;
}

