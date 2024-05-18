#include <stdio.h>
#include <errno.h>
#include "student.h"
// программа преобразует таблицу из текстового файла в бинарный

// Чтение данных студента из текстового файла
int ReadStudent(FILE* f, Student *s)
{
    return fscanf(f, "%[^:]:%[^:]:%[^:]:%[^:]:%u:%d:%d\n", s->surname, s->name, s->patronymic, s->group, &s->vaccination_fact, &s->mark_fundumental, &s->mark_architecture) == 7;
}

// аргументы argv имеют вид
// ./a.out <текстовый файл> <бинарный файл, по умолчанию "db_bin"> 
int main(int argc, char* argv[])
{
    if (argc != 2) {
        printf("Usage: program filename\n");
        return 1;
    }
    Student s;
    // in - текстовый файл, из которого считываем данные
    FILE *in = fopen(argv[1], "r");
    if (!in) {
        perror("Can't open file");
        return 2;
    } 

    // out - бинарный файл, в который записываем данные
    // Если не передаётся как аргумент, то по умолчанию равен "db_bin"
    FILE *out;
    if (argv[2]) {
    	out = fopen(argv[2], "w");
    }
    else {
    	out = fopen("db_bin", "w");
    }
    
    while (ReadStudent(in, &s))
        fwrite(&s, sizeof(s), 1, out);
    return 0;
}
