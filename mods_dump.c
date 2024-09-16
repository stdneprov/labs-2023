#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "mod.h"

void usage() {
    printf("Usage: mods_dump filename\n");
}

int read_mod(mod *m) {
    char line[256];
    if (fgets(line, sizeof(line), stdin)) {
        int result = sscanf(line, "%49[^\t]\t%49[^\t]\t%f\t%d\n", m->name, m->author, &m->rating, &m->downloads);
        if (result == 4) {
            printf("Read: %s, %s, %.2f, %d\n", m->name, m->author, m->rating, m->downloads);
            return 1;
        } else {
            printf("Failed to parse line: %s\n", line);
            return 0;
        }
    }
    return 0;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        usage();
        return 1;
    }

    FILE *out = fopen(argv[1], "wb");
    if (!out) {
        perror("Can't open file for writing");
        return 2;
    }

    mod m;
    while (read_mod(&m)) {
        printf("Writing: %s, %s, %.2f, %d\n", m.name, m.author, m.rating, m.downloads);
        fwrite(&m, sizeof(mod), 1, out);
    }

    fclose(out);
    return 0;
}
