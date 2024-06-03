#ifndef __Table__
#define __Table__
#include <stdbool.h>
#include <complex.h>

#define I _Complex_I

typedef struct Table {
    int val;
    double complex key;
    struct Table *last;
    struct Table *next;
    int size;
} Table;

Table TableInit();
void TablePush(Table *table, double a, double b, int value);
double complex TablePop(Table *table, double a, double b);
bool TableIsEmpty(Table *table);
void TablePrint(Table *table);
void TableFree(Table *table);
int TableSize(Table *table);
void Swap(Table *table);
void Sort(Table *table);
#endif