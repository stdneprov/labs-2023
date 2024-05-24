#ifndef __TABLE_H__
#define __TABLE_H__

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

/*
номер метода сортировки = ((N - 1) % 15) + 1 = ((6 - 1) % 15) + 1 = (5 % 15) + 1
= 5 + 1 = 6
    метод двоичной вставки
номер структуры таблицы = ((N + 5) % 9) + 1 = ((6 + 5) % 9) + 1 = (11 % 9) + 1 =
2 + 1 = 3
    тип ключа - строковый. Длина - 5 байтов. Хранение отдельно. Минимальное
число элементов - 13
*/

#define KEY_LEN 5
#define MAX_LEN 255
#define MIN_CAPACITY 13

typedef char t_key[KEY_LEN + 1];
typedef char t_val[MAX_LEN + 1];

typedef struct {
    t_key k;
    t_val v;
} Item;

typedef struct {
    Item **data;
    size_t size;
    size_t capacity;
    bool sorted;
} Table;

Table *TCreate(void);
void TReadFile(Table *t, FILE *fp);
void TInsert(Table *t, Item *i);
void TSort(Table *t);
Item *TGet(Table *t, const size_t i);
Item *TFind(Table *t, const t_key k);
void TPrint(const Table *t);
void TFree(Table *t);

Item *IFromFile(FILE *fp);

#endif
