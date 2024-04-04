#include <stdio.h>
#include <string.h>
#include "person.h"


// ./a.out output.bin -p (-f)
int main(int argc, char *argv[])
{
	Person p;
	FILE *file = NULL;

	if (argc < 3)
	{
		printf("Использование: %s файл флаг\nФлаги:\n-f - печать базы данных\n-p=[group] - выполнить задание\n", argv[0]);

		return 1;
	}

	file = fopen(argv[1], "rb");

	if (file == NULL)
	{
		printf("Произошла ошибка при открытии файла\n");

		return 1;
	}

	if (!strcmp(argv[2], "-f"))
	{
		printf("+----------------+----------+---------+--------+-------------+--------------+---------------+\n");
		printf("|    Фамилия     | Инициалы |   Пол   | Группа | Информатика | Лин. алгебра | Дискр. матем. |\n");
		printf("+----------------+----------+---------+--------+-------------+--------------+---------------+\n");

		while (fread(&p, sizeof(p), 1, file) == 1)
		{
			printf("|%16s|%10s|%9c|%8d|%13d|%14d|%15d|\n",
				p.fam,
				p.ini,
				p.gender,
				p.group,
				p.informat,
				p.linal,
				p.diskr
			);
		
			printf("+----------------+----------+---------+--------+-------------+--------------+---------------+\n");
		}
	} else if (strstr(argv[2], "-p=")) {
        printf("+----------------+----------+---------+--------+-------------+--------------+---------------+\n");
		printf("|    Фамилия     | Инициалы |   Пол   | Группа | Информатика | Лин. алгебра | Дискр. матем. |\n");
		printf("+----------------+----------+---------+--------+-------------+--------------+---------------+\n");

        char group[40] = "";
        strcpy(group, argv[2]);
        int group_int = 0;
        for (int i = 0; group[i] != '\0'; i++) {
            if (group[i] >= 48 && group[i] <= 57) {
                group_int *= 10;
                group_int += group[i] - '0';
            }
        }

        while (fread(&p, sizeof(p), 1, file) == 1) {
            if (p.gender == 'f' && p.group == group_int) {
                int count_five = 0;
                if (p.informat == 5) count_five += 1;
                if (p.linal == 5) count_five += 1;
                if (p.diskr == 5) count_five += 1;
                if (count_five == 1) {
                    printf("|%16s|%10s|%9c|%8d|%13d|%14d|%15d|\n",
				        p.fam,
                        p.ini,
                        p.gender,
                        p.group,
                        p.informat,
                        p.linal,
                        p.diskr
			        );
                }
                
            }
        }
		printf("+----------------+----------+---------+--------+-------------+--------------+---------------+\n");
    } else {
        printf("Использование: %s файл флаг\nФлаги:\n-f - печать базы данных\n-p=[group] - выполнить задание\n", argv[0]);
        return 0;
    }
	fclose(file);

	return 0;
}