#include <stdio.h>
#include <string.h>
#include "struct.h"

int main(int argc, char* argv[]){
    if (argc != 3){
        printf("too little arguments");
        return 1;
    }
    FILE *input = fopen(argv[1], "r");
    if (input == NULL){
        printf("couldn't open %s", argv[1]);
        return 1;
    }
    FILE *output = fopen(argv[2], "wb");
    if (output == NULL)
    {
        printf("couldn't open %s", argv[2]);
        fclose(input);
        return 1;
    }
    player p;
    while (fscanf(input, "%s %d %lf %d;\n", p.name, &p.games, &p.winRate, &p.mmr) == 4) {
        fwrite(&p, sizeof(player), 1, output);
    }
    fclose(input);
    fclose(output);

    printf("data successfully written to %s\n", argv[2]);

    return 0;
}