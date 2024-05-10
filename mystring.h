#ifndef __MY_STRING_H
#define __MY_STRING_H
#include <stdio.h>
#include <stdlib.h>

typedef struct String String;

struct String {
    char* begin;

    unsigned long int mem;
    unsigned long int size;
};

String* StringInit(char* chars);
void StringScan(FILE* file_in, String** string);
void StringAdd(String* string, char* chars);
String* StringSlice(String* string, int begin_idx, int end_idx);
void StringPrint(String* string);
void StringDelete(String** stringPtr);

#endif
