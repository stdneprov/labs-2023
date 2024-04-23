#ifndef __TEAM__
#define __TEAM__
#include <stdbool.h>


typedef struct team {
    char team_name[20];
    char project_name[20];
    int amount_people;
    int research_created;
    int research_checked;
    int defended;
} team;
#endif