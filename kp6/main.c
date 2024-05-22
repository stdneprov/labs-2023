#include "user.h"
#include "funcs.h"
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printfError("Неправильное количество аргументов.", 1);
    }
    FILE *src;
    FILE *dst;
    src = fopen(argv[1], "r");
    if (src == NULL) {
        printfError("Указанный файл не существует или не найден.", 2);
    }
    dst = fopen(argv[2], "wb");
    if (dst == NULL) {
        fclose(src);
        printfError("Указанный файл не существует или не найден.", 2);
    }
    User f;
    int total = 0;
    while (fscanf(src, "%99s %99s %d %d %d %d", f.username, f.status, &f.day,
                  &f.month, &f.year, &f.subs) == 6) {
        checkErr(src);
        const size_t written = fwrite(&f, sizeof(User), 1, dst);
        checkErr(dst);
        if (written != 1) {
            printfError("Error while writing data to file", 3);
        }
        total++;
    }
    checkErr(src);
    printf("%d", total);
    fclose(src);
    fclose(dst);
    return 0;
}
