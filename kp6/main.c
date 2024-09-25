#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "schedule.h"

// gcc main.c
// ./a.exe output.bin -f
// ./a.exe output.bin -p 100
int main(int argc, char *argv[])
{
	schedule t;
	FILE *file = NULL;

	if (argc < 3)
	{
		printf("Usage: %s <file> <flag>\nFlags:\n-f - show all schedule\n-p - show schedule in the particular classroom\n", argv[0]);
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
		printf(" ____________________________________________________________________________________________________________________\n");
        printf("|    Группа    |    день недели    |    номер пары    |     предмет     |    номер аудитории    | неделя (чет/нечет) |\n");
        printf("`--------------`-------------------`------------------`-----------------`-----------------------`--------------------`\n");

		while (fread(&t, sizeof(t), 1, file) == 1)
		{
			printf("|%14d|%19s|%18d|%17s|%23d|%20d|\n",
                t.group_number,
				t.day,
                t.lesson_number,
                t.subject,
                t.room_number,
                t.week
			);

		    printf("`--------------`-------------------`------------------`-----------------`-----------------------`--------------------`\n");
		}
	} else if (!strcmp(argv[2], "-p")) {
        int requiredRoomNumber = atoi(argv[3]);
        printf(" ____________________________________________________________________________________________________________________\n");
        printf("|    Группа    |    день недели    |    номер пары    |     предмет     |    номер аудитории    | неделя (чет/нечет) |\n");
        printf("`--------------`-------------------`------------------`-----------------`-----------------------`--------------------`\n");

        while (fread(&t, sizeof(t), 1, file) == 1) {
            if (t.room_number == requiredRoomNumber ) {
                    printf("|%14d|%19s|%18d|%17s|%23d|%20d|\n",
                        t.group_number,
				        t.day,
                        t.lesson_number,
                        t.subject,
                        t.room_number,
                        t.week
                    );
                    printf("`--------------`-------------------`------------------`-----------------`-----------------------`--------------------`\n");
            }
        }
    } else {
		printf("Usage: %s <file> <flag>\nFlags:\n-f - show all data base\n-p - show teams with proven research-doc\n", argv[0]);
        return 0;
    }
	fclose(file);

	return 0;
}