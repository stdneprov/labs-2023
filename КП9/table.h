#ifndef __Table__
#define __Table__
#include <stdbool.h>

typedef struct Table {
    int val;
    double key;
    struct Table *last;
    struct Table *next;
    int size;
} Table;

Table TableInit();
void TablePush(Table *table, double a, int value);
double TablePop(Table *table, double a);
bool TableIsEmpty(Table *table);
void TablePrint(Table *table);
void TableFree(Table *table);
int TableSize(Table *table);
void Swap(Table *table);
void TableSort(Table **table);
#endif
