#include <stdio.h>
#include "schedule.h"
// gcc convert_to_binary.c 
// ./a.exe output.bin data.txt
int main(int argc, char *argv[]) {
	schedule t;
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
        fscanf(file_in, "%d %s %d %s %d %d",
		&t.group_number,
		t.day,
        &t.lesson_number,
        t.subject,
        &t.room_number,
        &t.week
		);
        fwrite(&t, sizeof(t), 1, file_out);
    }
	fclose(file_out);
    fclose(file_in);
	return 0;
}