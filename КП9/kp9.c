#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 12

// Структура для хранения ключа и связанных с ним данных
typedef struct {
    double key;
    char data[100];
} Key;

// Функция бинарного поиска
int binary_search(Key table[], int n, double key) {
    int left = 0;
    int right = n - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (table[mid].key == key) {
            return mid;
        } else if (table[mid].key < key) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return -1;
}

// Функция для вывода таблицы
void print_table(Key table[], int n) {
    printf("Table state:\n");
    for (int i = 0; i < n; i++) {
        printf("%.2f %s\n", table[i].key, table[i].data);
    }
}

// Вспомогательная функция для обмена элементов
void swap(Key* a, Key* b) {
    Key temp = *a;
    *a = *b;
    *b = temp;
}

// Функция разбиения массива для быстрой сортировки
int partition(Key arr[], int low, int high) {
    double pivot = arr[high].key;
    int i = (low - 1);
    for (int j = low; j <= high - 1; j++) {
        if (arr[j].key <= pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

// Нерекурсивная реализация быстрой сортировки Хоара
void quicksort(Key arr[], int low, int high) {
    // Инициализация стека
    int stack[MAX];

    int top = -1;
    stack[++top] = low;
    stack[++top] = high;

    // Основной цикл пока стек не пуст
    while (top >= 0) {
        // Извлекаем high и low
        high = stack[top--];
        low = stack[top--];

        // Разбиение массива и получение индекса опорного элемента
        int p = partition(arr, low, high);

        // Если в левом подмассиве больше 1 элемента, добавляем его в стек
        if (p - 1 > low) {
            stack[++top] = low;
            stack[++top] = p - 1;
        }

        // Если в правом подмассиве больше 1 элемента, добавляем его в стек
        if (p + 1 < high) {
            stack[++top] = p + 1;
            stack[++top] = high;
        }
    }
}

int main() {
    int n;
    Key table[MAX];
    FILE *fp = fopen("text.txt", "r");
    if (fp == NULL) {
        printf("Error opening file\n");
        return 1;
    }

    n = 0;
    // Считываем данные из файла в таблицу
    while (fscanf(fp, "%lf %[^\n]", &table[n].key, table[n].data) != EOF && n < MAX) {
        n++;
        if (n >= MAX) 
            break;
    }
    fclose(fp);

    // Вывод таблицы
    print_table(table, n);

    // Сортировка таблицы с использованием быстрой сортировки и вывод после неё
    quicksort(table, 0, n - 1);
    printf("\nSorted table:\n");
    print_table(table, n);

    // Поиск ключа в отсортированной таблице
    double search_key;
    scanf("%lf", &search_key);
    int index = binary_search(table, n, search_key);
    if (index != -1) {
        printf("Key %.2f found at index: %d\n", table[index].key, index);
    } else {
        printf("Key %.2f not found in the table\n", search_key);
    }

    return 0;
}
