#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef enum {Vaccinated, Not_Vaccinated, Med_Withdrawal, Underage} Vaccination;

typedef struct student
{
    char surname[20];
    char name[20];
    char patronymic[20];
    char group[15];
    Vaccination vaccination_fact;
    int mark_fundumental;
    int mark_architecture;
} Student;

// Преобразует факт вакцинирования в строку 
char* StringFromVaccType(Vaccination v);

// Указывает, если ли у студента долги по АрКИс и(или) ФИ
bool StudentHasDebts(const Student* const s);

// Указывает на факт вакцинирования (s->vaccination_fact == Vaccinated)
bool StudentVaccinated(const Student* const s);

// Выводит шапку общей таблицы
void StudentsHeader();

// Выводит шапку таблицы с удачливыми должниками
void StudentDebtHeader();

// Выводит студента в общей таблице
void StudentPrint(Student* s);

// Выводит студента в таблице с долгами
void StudentDebtPrint(Student* s);
