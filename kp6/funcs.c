#include "funcs.h"
#include <stdlib.h> 
#include <stdio.h>
void printfError(char *str, int err) {
    fprintf(stderr, "%s", str);
    exit(err);
}

FILE *fileOpen(char *files[], int index, char *mode) {
    FILE *file = fopen(files[index], mode);
    if (file == NULL) {
        printfError("Указанный файл не существует или не найден.", 2);
    }
    return file;
}

void checkErr(FILE *file) {
    if (ferror(file)) {
        printfError("Error while reading/writing file", 8);
    }
}