#include <stdio.h>
#include <string.h>
#include "team.h"

// gcc main.c
// ./a.out output.bin -p (-f)
int main(int argc, char *argv[])
{
	team t;
	FILE *file = NULL;

	if (argc < 3)
	{
		printf("Usage: %s <file> <flag>\nFlags:\n-f - show all data base\n-p - show teams with proven research-doc\n", argv[0]);
		return 1;
	}

	file = fopen(argv[1], "rb");

	if (file == NULL)
	{
		printf("Error with %s\n", argv[1]);

		return 1;
	}

	if (!strcmp(argv[2], "-f"))
	{
		printf("+----------------+---------------+------------+-----------------+-------------------+------+\n");
		printf("|    команда     |    проект     |   кол-во   | research сделан | research проверен | сдан |\n");
		printf("+----------------+---------------+------------+-----------------+-------------------+------+\n");

		while (fread(&t, sizeof(t), 1, file) == 1)
		{
			printf("|%16s|%15s|%12d|%17d|%19d|%6d|\n",
                t.team_name,
				t.project_name,
                t.amount_people,
                t.research_created,
                t.research_checked,
                t.defended
			);

		    printf("+----------------+---------------+------------+-----------------+-------------------+------+\n");
		}
	} else if (!strcmp(argv[2], "-p")) {
        printf("+----------------+---------------+------------+-----------------+-------------------+------+\n");
		printf("|    команда     |    проект     |   кол-во   | research сделан | research проверен | сдан |\n");
		printf("+----------------+---------------+------------+-----------------+-------------------+------+\n");

        while (fread(&t, sizeof(t), 1, file) == 1) {
            if (t.research_checked == 1) {
                    printf("|%16s|%15s|%12d|%17d|%19d|%6d|\n",
                        t.team_name,
                        t.project_name,
                        t.amount_people,
                        t.research_created,
                        t.research_checked,
                        t.defended
                    );
                    printf("+----------------+---------------+------------+-----------------+-------------------+------+\n");

            }
        }
    } else {
		printf("Usage: %s <file> <flag>\nFlags:\n-f - show all data base\n-p - show teams with proven research-doc\n", argv[0]);
        return 0;
    }
	fclose(file);

	return 0;
}