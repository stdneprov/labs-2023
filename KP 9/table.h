#ifndef __TABLE__
#define __TABLE__
#define KEY_SIZE 9
#define MAX_LEN 256
#define MIN_CAPACITY 17

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct item {
    char key[10];
    char val[MAX_LEN];
} item;

typedef struct Table {
    item* rows;
    int size;
    int capacity;
} Table;

Table* CreateTable();
bool Add(Table* t, item r);
int Compare(char* a, char* b);
bool Buffer(Table* t);
void Print(Table* t);
void Destroy(Table* t);
int Search(Table* t, char* k);

#endif