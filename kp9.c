#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_RECORDS 100

typedef struct Key {
    long long int num;
    char lit;
} Key;

typedef struct Value {
    char value[150];
} Value;

typedef struct {
    Key key;
    char value[100];
} record_t;

void swap(Key* key1, Value* value1, Key* key2, Value* value2) {
    Key bufk = *key1;
    *key1 = *key2;
    *key2 = bufk;

    Value bufv = *value1;
    *value1 = *value2;
    *value2 = bufv;
}

long long int keycmp(Key key1, Key key2) {
    if (key1.num != key2.num) {
        return key1.num - key2.num;
    }
    else {
        return (int)key1.lit - (int)key2.lit;
    }
}

void PrintTable(Key* keys, Value* values, int n) {
    for(int i = 0; i < n; i++) {
        printf("%lld %c %s\n", keys[i].num, keys[i].lit, values[i]);
    }
}

void shake_sort(Key* keys, Value* values, int n) {
    int left = 0, right = n - 1, swapped = 1;

    while (left < right && swapped) {
        swapped = 0;
        for (int i = left; i < right; i++) {
            if (keycmp(keys[i], keys[i + 1]) > 0) {
                swap(&keys[i], &values[i], &keys[i+1], &values[i+1]);
                swapped = 1;
            }
        }
        right--;

        for (int i = right; i > left; i--) {
            if (keycmp(keys[i - 1], keys[i]) > 0) {
                swap(&keys[i-1], &values[i-1], &keys[i], &values[i]);
                swapped = 1;
            }
        }
        left++;
    }
}

int binary_search(Key* keys, Value* values, int left, int right, Key key) {
    while (left <= right) {
        int mid = left + (right - left) / 2;
        int cmp = keycmp(keys[mid], key);
        if (cmp == 0)
            return mid;
        else if (cmp < 0)
            left = mid + 1;
        else
            right = mid - 1;
    }
    return -1;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        return 1;
    }
    FILE *fp = fopen(argv[1], "r");
    if (!fp) {
        printf("Error opening file\n");
        return 1;
    }

    Key keys[MAX_RECORDS];
    Value values[MAX_RECORDS];

    int n = 0;
    int i = 0;
    char c;
    printf("hello\n");
    while (n <= MAX_RECORDS && fscanf(fp, "%lld %c    ", &(keys[n].num), &(keys[n].lit)) == 2) {
        i = 0;
        c = 0;
        while (i < 100) {
            c = fgetc(fp);
            if (c == '\n') {
                break;
            }
            values[n].value[i] = c;
            i++;
        }
        n++;
    }
    printf("Before sort:\n");
    PrintTable(keys, values, n);

    shake_sort(keys, values, n);

    printf("\nAfter sort:\n");
    PrintTable(keys, values, n);

    Key search_key;
    printf("Enter a key to search: ");
    scanf("%lld %c", &(search_key.num), &(search_key.lit));

    int index = binary_search(keys, values, 0, n - 1, search_key);
    if (index == -1)
        printf("Key not found\n");
    else
        printf("Key found: %lld %c, Value: %s\n", keys[index].num, keys[index].lit, values[index]);

    fclose(fp);
    return 0;
}
