#include <stdbool.h>
#include <stdio.h>

#include <string.h>
#include <stdlib.h>

#include "table.h"

int main(int argc, char **argw) {
    if (argc == 1) {
        fprintf(stderr, "ERROR: no input file supplied\n");
        exit(EXIT_FAILURE);
    }

    Table *t = TCreate();
    FILE *fp = fopen(argw[1], "r");
    if (fp == NULL) {
        fprintf(stderr, "ERROR: failed to open file: %s\n", argw[1]);
        exit(EXIT_FAILURE);
    }
    TReadFile(t, fp);

    printf("Table entered:\n");
    TPrint(t);
    printf("--------------\n");

    TSort(t);

    printf("Table sorted:\n");
    TPrint(t);
    printf("--------------\n");

    char *key = NULL;
    size_t len = 0;
    int read;
    printf("> ");
    while ((read = getline(&key, &len, stdin)) != -1) {
        if (read - 1 > KEY_LEN) {
            printf("ERROR: key length cannot be greater than %d\n> ", KEY_LEN);
            continue;
        }
        key[read - 1] = 0;
        Item *i = TFind(t, key);
        if (!i) {
            printf("ERROR: key [%s] no found in table\n> ", key);
            continue;
        }
        printf("%s:\t%s\n> ", i->k, i->v);
    }
    TFree(t);
}
