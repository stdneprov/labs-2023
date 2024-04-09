#ifndef _ITEM_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

#define _ITEM_H
#define KEY_SIZE 8
#define MAX_LEN_VALUE 1024


typedef struct {
    // long int key;
    long int key;
    char val[MAX_LEN_VALUE];
} item;

typedef struct Table {
    item* rows;
    int size;
    int capacity;
} Table;

int KeyCMP(long int key1, long int key2);

Table* CreateTable();
// Adds row to the end of the table

bool Add(Table* t, item r);

static bool Buffer(Table* t);

// Prints table content to the stdout
void Print(Table* t);

// Destroys table
void Destroy(Table* t);

// Binary search (only for sorted table)
int Search(Table* t, long int k);

#endif