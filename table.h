#ifndef _TABLE_H_
#define _TABLE_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


typedef struct Table Table;
typedef struct DataType DataType;
typedef DataType* TableAllocator;

typedef char KeyType;
typedef int ValueType;

struct Table {
    TableAllocator begin;

    size_t mem;
    size_t size;
};

struct Complex {
    int real;
    int imaginary;
};

struct DataType {
    KeyType key[7];
    ValueType value;
};


DataType ToDataType(const KeyType[7], const ValueType);
void DataTypePrint(const DataType*);

bool KeyTypeLess(const KeyType[7], const KeyType[7]);

void TableCreate(Table**);
bool TableIsEmpty(const Table*);
size_t TableSize(const Table*);

void TableInsert(Table*, const int, const DataType);
void TablePushBack(Table*, const DataType);
void TableRemove(Table*, const int);
void TablePopBack(Table*);

void TableShellSort(Table*, int);
DataType* TableLowerBound(const Table*, const KeyType[7]);
DataType* TableUpperBound(const Table*, const KeyType[7]);

void TablePrint(const Table*);
void TableClear(Table*);
void TableDelete(Table**);

#endif