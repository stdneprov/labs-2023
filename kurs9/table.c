#include "table.h"

#include <stdbool.h>
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
    t->data = malloc(t->capacity * sizeof(Item));
    return t;
}

void TInsert(Table *t, Item *i) {
    if (t->size + 1 > t->capacity) {
        t->capacity += MIN_CAPACITY;
        t->data = realloc(t->data, t->capacity * sizeof(Item));
        if (!t->data) {
            fprintf(stderr, "ERROR: buy more ram!\n");
            exit(EXIT_FAILURE);
        }
    }
    t->data[t->size++] = i;
    t->sorted = false;
}

size_t binarySearch(Table *t, const t_key k, int l, int r) {
    while (l < r) {
        int mid = (l + r) / 2;
        if (strcmp(k, t->data[mid]->k) == 0) {
            return mid;
        } else if (strcmp(k, t->data[mid]->k) > 0) {
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }
    return (strcmp(k, t->data[l]->k) > 0) ? (l + 1) : l;
}

void TSort(Table *t) {
    for (size_t i = 1; i < t->size; i++) {
        Item *selected = t->data[i];
        int loc = binarySearch(t, selected->k, 0, i - 1);
        for (int j = i; j > loc; j--) {
            t->data[j] = t->data[j - 1];
        }
        t->data[loc] = selected;
    }
    t->sorted = true;
}

Item *TFind(Table *t, const t_key k) {
    if (!t->sorted) {
        TSort(t);
    }
    size_t pos = binarySearch(t, k, 0, t->size - 1);
    if (pos >= t->size || strcmp(k, t->data[pos]->k) != 0)
        return NULL;
    return t->data[pos];
}

Item *TGet(Table *t, const size_t i) {
    if (i >= t->size)
        return NULL;
    return t->data[i];
}

void TPrint(const Table *t) {
    for (size_t i = 0; i < t->size; i++) {
        printf("%s:\t%s\n", t->data[i]->k, t->data[i]->v);
    }
}

void TFree(Table *t) {
    for (size_t i = 0; i < t->size; i++) {
        free(t->data[i]);
    }
    free(t->data);
    free(t);
}

void TReadFile(Table *t, FILE *fp) {
    Item *i = IFromFile(fp);
    while (i) {
        TInsert(t, i);
        i = IFromFile(fp);
    }
}

Item *IFromFile(FILE *fp) {
    bool done = false;
    char c = fgetc(fp);
    if (c == EOF)
        return NULL;

    Item *res = malloc(sizeof(Item));
    memset(res, 0, sizeof(Item));
    res->k[0] = c;
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
        res->k[i] = c;
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
            return res;
        }
        if (c == '\n') {
            done = true;
            break;
        }
        res->v[i] = c;
    }
    if (!done) {
        fprintf(stderr,
                "ERROR: value field cannot be longer than %d characters\n",
                MAX_LEN);
        exit(EXIT_FAILURE);
    }
    return res;
}
