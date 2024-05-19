// #ifndef STRUCT_H
// #define STRUCT_H

// typedef struct player {
//     char username[20];
//     int gameCount;
//     double wins;
//     int MMR;
// } player;

// #endif

#include "stdio.h"

typedef struct player
{
    char name[20];
    int games;
    double winRate;
    int mmr;
} player;