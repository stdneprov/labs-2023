#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "mod.h"

void usage() {
    printf("Usage: filter_mods filename [-f] | [-p <min_rating> <max_rating>]\n");
    printf("If <min_rating> or <max_rating> is omitted, the range is unbounded on that side.\n");
}

void print_mod(mod *m) {
    printf("%-50s %-50s %5.2f %10d\n", m->name, m->author, m->rating, m->downloads);
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        usage();
        return 1;
    }

    FILE *in = fopen(argv[1], "rb");
    if (!in) {
        perror("Can't open file for reading");
        return 2;
    }

    if (argc == 2 || (argc == 3 && strcmp(argv[2], "-f") == 0)) {
        mod m;
        printf("%-50s %-50s %5s %10s\n", "Name", "Author", "Rating", "Downloads");
        while (fread(&m, sizeof(mod), 1, in) == 1) {
            print_mod(&m);
        }
    } else if (argc >= 3 && strcmp(argv[2], "-p") == 0) {
        float min_rating = -1.0;
        float max_rating = 10.0;

        if (argc > 3 && strcmp(argv[3], "-") != 0) {
            min_rating = atof(argv[3]);
        }
        if (argc > 4 && strcmp(argv[4], "-") != 0) {
            max_rating = atof(argv[4]);
        }

        mod m;
        printf("%-50s %-50s %5s %10s\n", "Name", "Author", "Rating", "Downloads");
        while (fread(&m, sizeof(mod), 1, in) == 1) {
            if (m.rating >= min_rating && m.rating <= max_rating) {
                print_mod(&m);
            }
        }
    } else {
        usage();
        fclose(in);
        return 1;
    }

    fclose(in);
    return 0;
}
