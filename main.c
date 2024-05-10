#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mystring.h"
#include "student.h"

//Пытался в динамические строки, не получилось

int main(int argc, char *argv[])
{
	Student student;
	FILE *file = NULL;

	if (argc < 3)
	{
		printf("Использование: %s <file> <flag>\nFlags:\n-f - показать всю табличку\n-p - показать бедолаг\n", argv[0]);
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
		printf("+--------------------+--------------------+--------------------+----------+----+------+\n");
		printf("|      Фамилия       |        Имя         |      Отчество      | Прививка | ФИ | АКИС |\n");
		printf("+--------------------+--------------------+--------------------+----------+----+------+\n");

		while (fread(&student, sizeof(student), 1, file) == 1)
		{
			printf("|%20s|%20s|%20s|%10d|%4d|%6d|\n",
                student.middle_name,
				student.first_name,
                student.last_name,
                student.vac,
                student.mark_FI,
                student.mark_AoCaIS
			);

		    printf("+--------------------+--------------------+--------------------+----------+----+------+\n");
		}
	} else if (!strcmp(argv[2], "-p")) {
        printf("+--------------------+--------------------+--------------------+----------+----+------+\n");
		printf("|      Фамилия       |        Имя         |      Отчество      | Прививка | ФИ | АКИС |\n");
		printf("+--------------------+--------------------+--------------------+----------+----+------+\n");

        while (fread(&student, sizeof(student), 1, file) == 1) {
            if (student.vac == NO && student.mark_FI < 3 && student.mark_AoCaIS < 3) {
                    printf("|%20s|%20s|%20s|%10d|%4d|%6d|\n",
                    student.middle_name,
                    student.first_name,
                    student.last_name,
                    student.vac,
                    student.mark_FI,
                    student.mark_AoCaIS
                );

                printf("+--------------------+--------------------+--------------------+----------+----+------+\n");
            }
        }
    } else {
		printf("Использование: %s <file> <flag>\nFlags:\n-f - показать всю табличку\n-p - показать бедолаг\n", argv[0]);
        return 0;
    }
	fclose(file);

	return 0;
}