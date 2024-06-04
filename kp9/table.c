#include "table.h"
#include <stdio.h>

void Swap(Key* key1, Value* value1, Key* key2, Value* value2) {
    Key bufk = *key1;
    *key1 = *key2;
    *key2 = bufk;

    Value bufv = *value1;
    *value1 = *value2;
    *value2 = bufv;
}

int KeyCmp(Key key1, Key key2) {
    if (key1.num != key2.num) {  // сравнение по инту
        return key1.num - key2.num;
    }
    else {  // сравнение по литере
        return (int)key1.lit - (int)key2.lit;
    }
}

void PrintTable(Key* keys, Value* values, int n) {
    for(int i = 0; i < n; i++) {
        printf("%d %c %s\n", keys[i].num, keys[i].lit, values[i].value);
    }
}

void SelectionSort(Key* keys, Value* values, int n) {
    for (int i = 0; i < n - 1; i++) {
        int min_index = i;
        for (int j = i + 1; j < n; j++) {
            if (KeyCmp(keys[j], keys[min_index]) < 0) {
                min_index = j;
            }
        }
        if (min_index != i) {
            Swap(&keys[i], &values[i], &keys[min_index], &values[min_index]);
        }
    }
}

int BinarySearch(Key* keys, Value* values, int left, int right, Key key) {
    while (left <= right) {
        int mid = left + (right - left) / 2;
        int cmp = KeyCmp(keys[mid], key);
        if (cmp == 0)
            return mid;
        else if (cmp < 0)
            left = mid + 1;
        else
            right = mid - 1;
    }
    return -1;
}
