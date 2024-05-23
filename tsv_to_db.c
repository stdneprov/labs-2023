#include <stdio.h>
#include <stdlib.h>
#include "server.h"

int ReadServer(FILE *from, Server* server) {
    int a1, a2, a3, a4;
    int r = fscanf(from, "%s\t%d.%d.%d.%d\t%d", &(server->name), &a1, &a2, &a3, &a4, &(server->active));
    server->ip = (a1 << 24) + (a2 << 16) + (a3 << 8) + a4;
    return r;
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        return 1;
    }
    FILE *from = fopen(argv[1], "r");
    FILE *out = fopen(argv[2], "wb");
    if ((!from) || (!out)) {
        return 2;
    }
    Server s;
    while(ReadServer(from, &s) != EOF){
        fwrite(&s, sizeof(s), 1, out);
    }
    fclose(from);
    fclose(out);
}
