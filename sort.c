#include "sort.h"
#include "stdlib.h"

void QuickSort(Table *t) {
    int low = 0;
    int high = t->size - 1;
    int stack[high - low + 1];
    int top = -1;
    stack[++top] = low;
    stack[++top] = high;

    while (top >= 0) {
        high = stack[top--];
        low = stack[top--];

        double pivot = t->rows[high].key;
        int i = low;
        int j = high;

        while (i < j) {
            while (t->rows[i].key < pivot) {
                i++;
            }

            while (t->rows[j].key > pivot) {
                j--;
            }

            if (i <= j) {
                item tmp = t->rows[i];
                t->rows[i] = t->rows[j];
                t->rows[j] = tmp;
                i++;
                j--;
            }
        }

        if (low < j) {
            stack[++top] = low;
            stack[++top] = j;
        }

        if (high > i) {
            stack[++top] = i;
            stack[++top] = high;
        }
    }
}



