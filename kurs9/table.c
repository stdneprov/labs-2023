#include "table.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Table *TCreate(void) {
    Table *t = malloc(sizeof(Table));
    if (!t) {
        fprintf(stderr, "ERROR: buy more ram!\n");
        exit(EXIT_FAILURE);
    }
    t->capacity = MIN_CAPACITY;
    t->sorted = false;
    t->size = 0;
    t->keys = malloc(t->capacity * sizeof(t_key *));
    t->vals = malloc(t->capacity * sizeof(t_val *));
    return t;
}

void TInsert(Table *t, t_key k, t_val v) {
    if (t->size + 1 > t->capacity) {
        t->capacity += MIN_CAPACITY;
        t->keys = realloc(t->keys, t->capacity * sizeof(t_key *));
        if (!t->keys) {
            fprintf(stderr, "ERROR: buy more ram!\n");
            exit(EXIT_FAILURE);
        }
        t->vals = realloc(t->vals, t->capacity * sizeof(t_val *));
        if (!t->vals) {
            fprintf(stderr, "ERROR: buy more ram!\n");
            exit(EXIT_FAILURE);
        }
    }
    t_key *key = malloc(sizeof(t_key));
    t_val *val = malloc(sizeof(t_val));
    if (!key || !val) {
        fprintf(stderr, "ERROR: buy more ram!\n");
        exit(EXIT_FAILURE);
    }
    memcpy(key, k, sizeof(t_key));
    memcpy(val, v, sizeof(t_val));
    t->keys[t->size] = key;
    t->vals[t->size] = val;
    t->size++;
    t->sorted = false;
}

size_t binarySearch(Table *t, const t_key k, int l, int r) {
    while (l < r) {
        int mid = (l + r) / 2;
        if (strcmp(k, *(t->keys[mid])) == 0) {
            return mid;
        } else if (strcmp(k, *(t->keys[mid])) > 0) {
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }
    return (strcmp(k, *(t->keys[l])) > 0) ? (l + 1) : l;
}

void TSort(Table *t) {
    for (size_t i = 1; i < t->size; i++) {
        t_key *selected = t->keys[i];
        t_val *selected_data = t->vals[i];
        int loc = binarySearch(t, *selected, 0, i - 1);
        for (int j = i; j > loc; j--) {
            t->keys[j] = t->keys[j - 1];
            t->vals[j] = t->vals[j - 1];
        }
        t->keys[loc] = selected;
        t->vals[loc] = selected_data;
    }
    t->sorted = true;
}

t_val *TFind(Table *t, const t_key k) {
    if (!t->sorted) {
        TSort(t);
    }
    size_t pos = binarySearch(t, k, 0, t->size - 1);
    if (pos >= t->size || strcmp(k, *t->keys[pos]) != 0)
        return NULL;
    return t->vals[pos];
}

t_val *TGet(Table *t, const size_t i) {
    if (i >= t->size)
        return NULL;
    return t->vals[i];
}

void TPrint(const Table *t) {
    for (size_t i = 0; i < t->size; i++) {
        printf("%s:\t%s\n", *t->keys[i], *t->vals[i]);
    }
}

void TFree(Table *t) {
    for (size_t i = 0; i < t->size; i++) {
        free(t->keys[i]);
        free(t->vals[i]);
    }
    free(t->keys);
    free(t->vals);
    free(t);
}

void TReadFile(Table *t, FILE *fp) {
    t_key k;
    t_val v;
    bool res = IFromFile(fp, &k, &v);

    while (res) {
        TInsert(t, k, v);
        res = IFromFile(fp, &k, &v);
    }
}

bool IFromFile(FILE *fp, t_key *k, t_val *v) {
    bool done = false;
    char c = fgetc(fp);
    if (c == EOF)
        return false;

    memset(k, 0, sizeof(t_key));
    memset(v, 0, sizeof(t_val));
    (*k)[0] = c;
    for (int i = 1; i < KEY_LEN + 1; i++) {
        char c = fgetc(fp);
        if (c == EOF) {
            fprintf(stderr, "ERROR: incomplete field\n");
            exit(EXIT_FAILURE);
        }
        if (c == '\t') {
            done = true;
            break;
        }
        (*k)[i] = c;
    }
    if (!done) {
        fprintf(stderr,
                "ERROR: key field cannot be longer than %d characters\n",
                KEY_LEN);
        exit(EXIT_FAILURE);
    }
    done = false;
    for (int i = 0; i < MAX_LEN + 1; i++) {
        char c = fgetc(fp);
        if (c == EOF) {
            return true;
        }
        if (c == '\n') {
            done = true;
            break;
        }
        (*v)[i] = c;
    }
    if (!done) {
        fprintf(stderr,
                "ERROR: value field cannot be longer than %d characters\n",
                MAX_LEN);
        exit(EXIT_FAILURE);
    }
    return true;
}
