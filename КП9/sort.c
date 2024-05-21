#include <stdio.h>      /* Standard Library of Input and Output */
#include <complex.h>    /* Standard Library of Complex Numbers */
#include "slovar.h"
#include <string.h>

void Swap(Table *table) {
    double complex s = table->key;
    int valuev = table->val;
    table->key = table->next->key;
    table->val = table->next->val;
    table->next->key = s;
    table->next->val = valuev;
}

void Sort(Table *table) {
    while(table->next != NULL) {
        if ((creal(table->next->key) * creal(table->next->key) + cimag(table->next->key) * cimag(table->next->key))  < (creal(table->key) * creal(table->key) + cimag(table->key) * cimag(table->key))) {
            Swap(table);
        }
        table = table->next;
    }
}