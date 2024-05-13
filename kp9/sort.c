#include "sort.h"

void BubbleSort(Table *t) {
    for (int i = 1; i < t->size; i++) {
        for (int j = 0; j < t->size - i; j++) {
            if (t->rows[j].key > t->rows[j+1].key) {
                item tmp = t->rows[j];
                t->rows[j] = t->rows[j+1];
                t->rows[j+1] = tmp;
            }
        }
    }
}