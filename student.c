#include "student.h"

char* StringFromVaccType(Vaccination v) {
    char *vacc_strings[] = {"Привит", "Не привит", "Мед. отвод", "Нет 18"};
    return vacc_strings[v];
}

bool StudentHasDebts(const Student* const s) {
    if (!s) {
        return false;
    }
    return ((s->mark_architecture == 2) || (s->mark_fundumental == 2));
}

bool StudentVaccinated(const Student* const s) {
    if (!s) {
        return false;
    }
    return (s->vaccination_fact == 0);
}

void StudentsHeader() {
    printf("  Full name                    | Group |   Vaccinated   | Arch mark | Fund mark\n");
}

void StudentDebtHeader() {
    printf("  Full name                      | Group      | Debts\n");
}

void StudentPrint(Student* s) {
	if (!s) {
		return;
	}
    // Строка name содержит ФИО студента
	char name[80];
	strcpy(name, s->surname);
    strcat(name, " ");
    strcat(name, s->name);
    strcat(name, " ");
    strcat(name, s->patronymic);
    printf("%-35s %s %s %d %d\n", name, s->group, StringFromVaccType(s->vaccination_fact), s->mark_architecture, s->mark_fundumental);
}

char* ListStudentDebts(const Student* const s) {
    if (!s || (StudentHasDebts(s) == false)) {
        return NULL;
    }
    char* debt = malloc(10 * sizeof(char));
    if (s->mark_architecture == 2) {
        strcat(debt, "Arch");
        if (s->mark_fundumental == 2) {
            strcat(debt, " and ");
        }
    } 
    if (s->mark_fundumental == 2) {
    	strcat(debt, "FI");
    }
    strcat(debt, "\n");
    return debt;
}

void StudentDebtPrint(Student* s) {
	if (!s) {
		return;
	}
	char name[80];
	strcpy(name, s->surname);
    strcat(name, " ");
    strcat(name, s->name);
    strcat(name, " ");
    strcat(name, s->patronymic);
    printf("%s из группы %s спасён! Он сможет избежать двойки за %s", name, s->group, ListStudentDebts(s));
    //printf("%-35s %s %s", name, s->group, ListStudentDebts(s));
}
