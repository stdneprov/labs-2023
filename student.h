#include <stdio.h>
#include "mystring.h"

typedef struct Student Student;

enum vaccinated{NO, YES, MEDOTVOD, TOO_YOUNG};

struct Student {
    char middle_name[20];
    char first_name[20];
    char last_name[20];
    enum vaccinated vac;
    int mark_FI;
    int mark_AoCaIS;
};
