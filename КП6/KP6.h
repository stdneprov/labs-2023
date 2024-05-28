#ifndef __MOD__
#define __MOD__
#include <stdbool.h>


typedef struct mod {
    char mod_name[20];
    char creator_name[20];
    float rating;
    int amount_of_loads;
} mod;
#endif