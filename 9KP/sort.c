#include "sort.h"

void Swap(item *a, item *b) {
    item temp = *a;
    *a = *b;
    *b = temp;
}

void Sort(Table* t) {
    int isSorted = 1;
    int k = 0;
    for (int i = 0; i < t->size; i++) {
        for(int j = (i % 2) ? 0 : 1; j + 1 < t->size; j += 2) {
            if (strcmp(t->rows[j].val, t->rows[j + 1].val) > 0) {
                isSorted = 0;
                Swap(&t->rows[j], &t->rows[j + 1]);
            }
        }
        k++;
        if (isSorted == 1 && k % 2 == 0) {
            break;
        } else {
            isSorted = 1;
            continue;
        }
        
    }
}

void Reverse(Table* t) {
    for(int i = 0; i < t->size / 2; ++i)
        Swap(&t->rows[i], &t->rows[t->size - i - 1]);
}

void Shuffle(Table* t) {
    srand (time(NULL));
    for(int i = t->size - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        Swap(&t->rows[i], &t->rows[j]);
    }
}