#include <stdio.h>
#include <stdlib.h>
#include "item.h"

void PrintItem(Item* i) {
    if (i->type == NUMBER) {
        printf("%lf", i->value.number);
    } else if (i->type == OPERATOR) {
        if (i->value.operator.c == '(') printf(" (");
        else if (i->value.operator.c == ')') printf(") ");
        else printf(" %c ", i->value.operator);
    } else {
        int lenVar = i->value.str->lenStr;
        char* str = i->value.str->chars;
        for (int j = 0; j < lenVar; j++){
            printf("%c", str[j]);
        }
    }
}

void DelItem(Item *i) {
    if (i->type == NUMBER) {
        free(i);
    } else if (i->type == OPERATOR) {
        free(i);
    } else {
        free(i->value.str->chars);
        free(i->value.str);
        free(i);
    }
}