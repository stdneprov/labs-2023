#include <stdio.h>
#include "person.h"

int readPerson(Person *p)
{
	int ret = scanf("%s %s %c %d %d %d %d",
		p->fam,
		p->ini,
		&p->gender,
		&p->group,
		&p->informat,
		&p->linal,
		&p->diskr
	);
	
	return (ret == 7);
}



// ./a.out output.bin groups.txt
int main(int argc, char *argv[]) {
	Person p;
	FILE *file_out = NULL;
    FILE *file_in = NULL;

	if (argc != 3) {
		printf("Usage: %s output.bin input.txt\n", argv[0]);
		return 1;
	}

	file_out = fopen(argv[1], "wb");
	if (file_out == NULL) {
		printf("Произошла ошибка при открытии файла\n");
		return 1;
	}
    file_in = fopen(argv[2], "r");
    if (file_in == NULL) {
		printf("Произошла ошибка при открытии файла\n");
		return 1;
	}
    
    while (!feof(file_in)) {
        fscanf(file_in, "%s %s %c %d %d %d %d",
		p.fam,
		p.ini,
		&p.gender,
		&p.group,
		&p.informat,
		&p.linal,
		&p.diskr);
        fwrite(&p, sizeof(p), 1, file_out);
    }

	fclose(file_out);
    fclose(file_in);
	return 0;
}

