#ifndef __TABLE__
#define __TABLE__
#define KEY_SIZE 4
#define MAX_LEN 256
#define MIN_CAPACITY 16

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct item {
    float key;
    char val[MAX_LEN];
} item;

typedef struct Table {
    item* rows;
    int size;
    int capacity;
} Table;

Table* CreateTable();
bool Add(Table* t, item r);
bool Buffer(Table* t);
void Print(Table* t);
void Destroy(Table* t);
int Search(Table* t, float k);

#endif