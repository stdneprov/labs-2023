#include "struct.h"

int main(int arg, char* argv[]){
    dota pip;
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
    while (fscanf(in, "%99[^\t]\t%d\t%lf\t%d;\n", pip.name, &pip.games, &pip.percent, &pip.MMR) == 4) {
        fwrite(&pip, sizeof(dota), 1, out);
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