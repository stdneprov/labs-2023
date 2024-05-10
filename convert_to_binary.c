#include <stdio.h>
#include "student.h"
#include "mystring.h"

// gcc convert_to_binary.c 
// ./a.out output.bin data.txt

int main(int argc, char *argv[]) {
	Student student;
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

        // StringScan(file_in, &student.middle_name);
        // StringScan(file_in, &student.first_name);
        // StringScan(file_in, &student.last_name);

		fscanf(file_in, "%s %s %s %d %d %d",
        student.middle_name,
        student.first_name,
        student.last_name,
		&student.vac,
        &student.mark_FI,
        &student.mark_AoCaIS
        );
        fwrite(&student, sizeof(student), 1, file_out);
    }
	fclose(file_out);
    fclose(file_in);
	return 0;
}