#include "table.h"
#include <stdlib.h>
#include <stdio.h>

Table TableInit() {
    Table new;
    new.size = 0;
    new.last = NULL;
    new.next = NULL;
    return new;
}

void TablePush(Table *table, double a, int value) {
    if (table->size == 0) {
        table->next = NULL;
        table->key = a;
        table->val = value;
        table->last = table;
    } else {
        Table* new = (Table *)malloc(sizeof(Table));
        if (new == NULL) {
            exit(-1);
        }
        new->key = a;
        new->val = value;
        table->last->next = new;
        new->next = NULL;
        table->last = table->last->next;
    }
    printf("Add complited\n");
    printf("key: %.2f\tvalue: %d\n", table->last->key, table->last->val);
    table->size++;
}

bool TableIsEmpty(Table *table) {
    return (table->size) == 0;
}

void TablePrint(Table *table) {
    while (table != NULL) {
        printf("key: %.2f\tvalue: %d\n",table->key, table->val);
        table = table->next;
    }
}

void TableFree(Table *table) {
    Table *next;
    for (Table *i = table; i != NULL; i = next) {
        next = i->next;
        free(i);
    }
}

int TableSize(Table *table) {
    return table->size;
}
