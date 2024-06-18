#include "s.h"

int main(int arg, char* argv[]){
    Table muf;
    if (arg != 3){
        fprintf(stderr, "Wrong args");
        return 1;
    }
    FILE* in = fopen(argv[1], "r");
    if (in == NULL){
        fprintf(stderr, "Wrong %s", argv[1]);
        return 2;
    }
    FILE* out = fopen(argv[2], "w");
    if (out == NULL)
    {
        fprintf(stderr, "Wrong %s", argv[2]);
        fclose(in);
        return 3;
    }
    while (fscanf(in, "%d\t%99[^\t]\t%d\t%99[^\t]\t%99[^\t]\t%99[^;];\n", &muf.gruppa, muf.day, &muf.number, muf.para, muf.room, muf.week) == 6) {
        fwrite(&muf, sizeof(Table), 1, out);
        if (ferror(out) != 0){
            fprintf(stderr, "Wrong out");
            return 4;
        }
    }
    if (ferror(in) != 0){
        fprintf(stderr, "Wrong in");
        return 5;
    }
    fclose(in);
    fclose(out);
    return 0;
}