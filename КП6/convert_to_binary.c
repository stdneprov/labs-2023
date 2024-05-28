#include <stdio.h>
#include "KP6.h"
int main(int argc, char *argv[]) {
	mod m;
	FILE *file_out = NULL;
    FILE *file_in = NULL;

	if (argc != 3) {
		printf("Usage: %s output.bin data.txt\n", argv[0]);
		return 1;
	}

	file_out = fopen(argv[1], "wb");
	if (file_out == NULL) {
		printf("Error with %s\n", argv[1]);
		return 1;
	}
    file_in = fopen(argv[2], "r");
    if (file_in == NULL) {
		printf("Error with %s\n", argv[2]);
		return 1;
	}

    while (!feof(file_in)) {
        fscanf(file_in, "%s %s %f %d",
		m.mod_name,
		m.creator_name,
		&m.rating,
		&m.amount_of_loads);
        fwrite(&m, sizeof(m), 1, file_out);
    }
	fclose(file_out);
    fclose(file_in);
	return 0;
}