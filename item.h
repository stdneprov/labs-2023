#ifndef __ITEM__
#define __ITEM__

#include <stdio.h>
#include <stdlib.h>

typedef struct Str {
    char* chars;
    int lenStr;
} Str;

typedef struct Oper {
    char c;
    int p;
} Oper;

typedef union Value {
    double number;
    Str *str;
    Oper operator;
} Value;

typedef enum Type {
    NUMBER, OPERATOR, VARIABLE
} Type;

typedef struct Item {
    Type type;
    Value value;
} Item;

void PrintItem(Item *i);
void DelItem(Item *i);

#endif