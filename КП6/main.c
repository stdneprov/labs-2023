#include <stdio.h>
#include <string.h>
#include "KP6.h"

int main(int argc, char *argv[])
{
	mod m;
	FILE *file = NULL;

    if (argc < 3)
	{
		printf("Usage: %s <file> <flag>\nFlags:\n-a - show all mods\n-c - show mods from certain creator (input creator name after that)\n", argv[0]);
		return 1;
	}

    file = fopen(argv[1], "rb");

	if (file == NULL)
	{
		printf("Error with %s\n", argv[1]);

		return 1;
	}

    	if (!strcmp(argv[2], "-a"))
	{
        printf("+--------------------+--------------------+-------------+-------------------+\n");
	    printf("|        Мод         |       Автор        |   Рейтинг   | Кол-во скачиваний |\n");
	    printf("+--------------------+--------------------+-------------+-------------------+\n");

		while (fread(&m, sizeof(m), 1, file) == 1) {
			printf("|%20s|%20s|%13f|%19d|\n",
                m.mod_name,
				m.creator_name,
                m.rating,
                m.amount_of_loads
			);

		    printf("+--------------------+--------------------+-------------+-------------------+\n");
        }

	} else if (!strcmp(argv[2], "-c")) {
        char creator[20];
        scanf("%20s", creator);

        printf("+--------------------+--------------------+-------------+-------------------+\n");
	    printf("|        Мод         |       Автор        |   Рейтинг   | Кол-во скачиваний |\n");
	    printf("+--------------------+--------------------+-------------+-------------------+\n");

		while (fread(&m, sizeof(m), 1, file) == 1) {
            if (!strcmp(creator, m.creator_name)) {
			printf("|%20s|%20s|%13.1f|%19d|\n",
                m.mod_name,
				m.creator_name,
                m.rating,
                m.amount_of_loads
			);

		    printf("+--------------------+--------------------+-------------+-------------------+\n");
            }

			if (feof(file)) {
				break;
			}
        }

    } else {
        printf("Usage: %s <file> <flag>\nFlags:\n-a - show all mods\n-c - show mods from certain creator (input creator name after that)\n", argv[0]);
        return 0;
    }

    fclose(file);

    return 0;
}
