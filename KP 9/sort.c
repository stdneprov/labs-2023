#include "sort.h"

void LinearWithCounting(Table *table) {
    int* counter = malloc(sizeof(int) * table->size + 1);
    memset(counter, 0, sizeof(int) * table->size);
    for (int i = 0; i < table->size; i++) {
        for (int j = i; j < table->size; j++) {
            if (Compare(table->rows[i].key, table->rows[j].key) == 1) {
                counter[i] += 1;
            } else if (Compare(table->rows[i].key, table->rows[j].key) == -1) {
                counter[j] += 1;
            }
        }
    }
    item temp_rows[table->size];
    int ind = 0;
    for (int i = 0; i < table->size + 1; i++) {
        for (int j = 0; j < table->size; j++) {
            if (counter[j] == i) {
                temp_rows[ind] = table->rows[j];
                ind += 1;
            }
        }
    }

    for (int i = 0; i < table->size; i++) {
        table->rows[i] = temp_rows[i];
    }
}