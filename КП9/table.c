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
    if (value == 11037) {
        printf("У нас не уважают такие числа, оно не будет записано");
        exit(-1);
    }
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
        //table->last = new;
    }
    printf("dobavleno\n");
    printf("key: %.2f\tvalue: %d\n", table->last->key, table->last->val);
    table->size++;
    //printf("!!!%d!!!\n", table->size);
}

bool TableIsEmpty(Table *table) {
    //printf(table->size);
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
