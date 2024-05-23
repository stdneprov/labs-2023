#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "table.h"

DataType ToDataType(const KeyType key[7], const ValueType value) {
    DataType data;
    strcpy(data.key, key);
    data.value = value;
    return data;
}

void DataTypePrint(const DataType* data) {
    printf("%8s|%8d", data->key, data->value);
}

bool KeyTypeLess(const KeyType lvalue[7], const KeyType rvalue[7]) {
    size_t llen = strlen(lvalue);
    size_t rlen = strlen(rvalue);
    if (llen < rlen) {
        for (int i = 0; i < llen; ++i) {
            if (lvalue[i] == rvalue[i]) {
                continue;
            } else {
                return (lvalue[i] < rvalue[i]);
            }
        }
        return true;
    } else {
        for (int i = 0; i < rlen; ++i) {
            if (lvalue[i] == rvalue[i]) {
                continue;
            } else {
                return (lvalue[i] < rvalue[i]);
            }
        }
        return false;
    }
}

void TableCreate(Table** table) {
    *table = (Table*)malloc(sizeof(Table));
    if (*table == NULL) {
        return;
    }
    
    (*table)->begin = malloc(11 * sizeof(DataType));
    if ((*table)->begin == NULL) {
        return;
    }

    (*table)->size = 0;
    (*table)->mem = 10;
}

bool TableIsEmpty(const Table* table) {
    return (table->size == 0);
}

size_t TableSize(const Table* table) {
    return table->size;
}

void TableInsert(Table* table, const int idx, const DataType data) {

    for (int i = table->size - 1; i >= idx; --i) {
        table->begin[i+1] = table->begin[i];
    }
    table->begin[idx] = data;
    
    ++(table->size);

    if (table->size == table->mem) {
        table->begin = (TableAllocator)realloc(table->begin, (((table->mem)*2 + 1) * sizeof(DataType)));
        (table->mem) *= 2;
    }
}

void TablePushBack(Table* table, const DataType data) {
    
    table->begin[table->size] = data;
    
    ++(table->size);

    if (table->size == table->mem) {
        table->begin = (TableAllocator)realloc(table->begin, (((table->mem)*2 + 1) * sizeof(DataType)));
        (table->mem) *= 2;
    }
}

void TableRemove(Table* table, const int idx) {

    --(table->size);

    for (int i = table->size - 1; i >= idx; --i) {
        table->begin[i] = table->begin[i+1];
    }

    if (table->size == (table->mem)/4 && table->mem > 10) {
        
        table->begin = (TableAllocator)realloc(table->begin, ((table->mem) / 2 + 1)*sizeof(DataType));
        table->mem /= 2;
    }
}

void TablePopBack(Table* table) {
    --(table->size);

    if (table->size == (table->mem)/4 && table->mem > 10) {
        
        table->begin = (TableAllocator)realloc(table->begin, ((table->mem) / 2 + 1)*sizeof(DataType));
        table->mem /= 2;
    }
}

void TableShellSort(Table* table, int d) {
    bool flag = true;
    while (flag) {
        flag = false;
        for (int i = d; i < table->size; ++i) {

            if (KeyTypeLess(table->begin[i].key, table->begin[i-d].key)) {
                DataType buff = table->begin[i];
                table->begin[i] = table->begin[i-d];
                table->begin[i-d] = buff;
                flag = true;
            }
        }
        if (d > 1) {
            d /= 2;
            flag = true;
        }
    }
}

DataType* TableLowerBound(const Table* table, const KeyType key[7]) {
    DataType* lb = table->begin;
    DataType* ub = &(table->begin[table->size - 1]);
    DataType* cur;

    while (ub - lb != 1) {
        cur = &(lb[(ub-lb)/2]);

        if (KeyTypeLess(key, cur->key)) {
            ub = cur;
        } else {
            lb = cur;
        }
    }

    return &(table->begin[lb-table->begin]);
}

DataType* TableUpperBound(const Table* table, const KeyType key[7]) {
    DataType* lb = table->begin;
    DataType* ub = &(table->begin[table->size - 1]);
    DataType* cur;

    while (ub - lb != 1) {
        cur = &(lb[(ub-lb)/2]);

        if (KeyTypeLess(key, cur->key)) {
            ub = cur;
        } else {
            lb = cur;
        }
    }

    return &(table->begin[ub-table->begin]);
}

void TablePrint(const Table* table) {
    if (TableIsEmpty(table)) {
        return;
    }
    printf("+----+--------+--------+\n| idx|   key  |  value |\n+----+--------+--------+\n");
    
    for (int i = 0; i < table->size; ++i) {
        printf("|%4d|", i);
        DataTypePrint(&(table->begin[i]));
        printf("|\n+----+--------+--------+\n");
    }
}

void TableClear(Table* table) {

    table->begin = (TableAllocator)realloc(table->begin, (11 * sizeof(DataType)));  

    table->size = 0;
    table->mem = 10;
}

void TableDelete(Table** table) {
    if (*table != NULL) {
        free((*table)->begin);
        free(*table);
        *table = NULL;
    }
}
