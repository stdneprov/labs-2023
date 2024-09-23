#ifndef __SCHEDULE__
#define __SCHEDULE__
#include <stdbool.h>


typedef struct schedule {
    char day[30];
    char subject[30];
    int group_number;
    int lesson_number;
    int room_number;
    int week;
} schedule;
#endif