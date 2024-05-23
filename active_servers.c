#include <stdio.h>
#include <stdlib.h>
#include "server.h"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        return 1;
    }
    FILE *from = fopen(argv[1], "r");
    if (!from) {
        return 2;
    }
    Server s;
    while (fread(&s, sizeof(s), 1, from) == 1) {
        if(s.active == 1) {
            printf("%s %ld.%ld.%ld.%ld\n", s.name, (s.ip >> 24) & 255, (s.ip >> 16) & 255, (s.ip >> 8) & 255, s.ip & 255);

        }
    }
}