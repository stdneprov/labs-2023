#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "struct.h"

void PrintPlayer(player p) {
    printf("%s %d %.2f%% %d;\n", p.name, p.games, p.winRate, p.mmr);
}

int CheckMMR(int mmr, char *flag) {
    if (strcmp(flag, "--herald") == 0) {
        return (mmr >= 0 && mmr <= 769);
    } else if (strcmp(flag, "--guardian") == 0) {
        return (mmr >= 770 && mmr <= 1539);
    } else if (strcmp(flag, "--crusader") == 0) {
        return (mmr >= 1540 && mmr <= 2309);
    } else if (strcmp(flag, "--archon") == 0) {
        return (mmr >= 2310 && mmr <= 3079);
    } else if (strcmp(flag, "--legend") == 0) {
        return (mmr >= 3080 && mmr <= 3849);
    } else if (strcmp(flag, "--ancient") == 0) {
        return (mmr >= 3850 && mmr <= 4619);
    } else if (strcmp(flag, "--divine") == 0) {
        return (mmr >= 4620 && mmr <= 5420);
    } else if (strcmp(flag, "--immortal") == 0) {
        return (mmr >= 5421);
    }
    return 0;
}

int main(int argc, char* argv[]){
    if (argc < 3) {
        printf("no flags entered");
        return 1;
    }
    FILE *input = fopen(argv[1], "rb");
    if (input == NULL){
        printf("couldn't open %s", argv[1]);
        return 2;
    }
    player p;
    int flagFound = 0;
    while (fread(&p, sizeof(player), 1, input)) {
        for (int i = 2; i < argc; i++) {
            if (CheckMMR(p.mmr, argv[i])) {
                PrintPlayer(p);
                flagFound = 1;
                break;
            }
        }
    }

    if (!flagFound) {
        printf("no players found for the flags\n");
    }

    fclose(input);
    return 0;
}