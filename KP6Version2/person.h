#ifndef PERSON_H
#define PERSON_H

typedef struct _Person
{
	char fam[17];	// Фамилия
	char ini[9];	// Инициалы
	char gender;	// Пол
	int group;		// Группа
	int informat;	// Информатика
	int linal;		// Лин. алгебра
	int diskr;		// Дискр. математика
} Person;

#endif