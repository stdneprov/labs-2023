#include <stdio.h>
#include "team.h"
// gcc convert_to_binary.c 
// ./a.out output.bin data.txt
int main(int argc, char *argv[]) {
	team t;
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
        fscanf(file_in, "%s %s %d %d %d %d",
		t.team_name,
		t.project_name,
		&t.amount_people,
		&t.research_created,
        &t.research_checked,
        &t.defended
		);
        fwrite(&t, sizeof(t), 1, file_out);
    }
	fclose(file_out);
    fclose(file_in);
	return 0;
}