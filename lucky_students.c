#include <stdlib.h>
#include <stdio.h>
#include "student.h"
// Программа выводит все данные из таблицы, содержащиеся в бинарном файле,
// либо данные удачливых должников

// аргументы argv имеют вид
// ./a.out <бинарный файл> <-f, указывается если нужно вывести всю таблицу>
int main(int argc, char* argv[])
{
    if (argc < 2) {
        printf("Usage: program filename\n");
        return 1;
    }
    FILE* in = fopen(argv[1], "rb");

    if (!in) {
        perror("Can't open file");
        return 2;
    }

    Student s;
    // Случай, если argv[2] == "-f", т.е надо вывести всех студентов
    if ((argc == 3) && (strncmp(argv[2], "-f", 2) == 0)) {
        StudentsHeader();
        while (fread(&s, sizeof(Student), 1, in) == 1) {
            StudentPrint(&s);
        } 
        fclose(in);
        return 0;
    }
	
    StudentDebtHeader();
    while (fread(&s, sizeof(Student), 1, in) == 1) {
        if (StudentHasDebts(&s) && StudentVaccinated(&s)) {
            StudentDebtPrint(&s);
        } 
    } 
    fclose(in);
    return 0;
}
