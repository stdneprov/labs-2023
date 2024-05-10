#include <stdio.h>
#include "mystring.h"

String* StringInit(char* chars) {
    String* string = (String*)malloc(sizeof(String));
    if (string == NULL) {
        return NULL;
    }
    
    string->begin = (char*)malloc(11 * sizeof(char));
    if (string->begin == NULL) {
        return NULL;
    }
    string->size = 0;
    string->mem = 10;

    StringAdd(string, chars);

    return string;
}

void StringScan(FILE* file_in, String** string) {
    *string = StringInit("");
    char in[1];
    fscanf(file_in, "%c", &in[0]);
    while (in[0] != ' ' || in[0] != '\n' || in[0] != EOF) {
        StringAdd(*string, in);
        fscanf(file_in, "%c", &in[0]);
    }
}

void StringAdd(String* string, char* chars) {
    int idx = 0;
    while (chars[idx] != 0) {
        string->begin[string->size] = chars[idx];
        ++(string->size);
        if (string->size == string->mem) {
            char* old = string->begin;
            string->begin = (char*)realloc(string->begin, (((string->mem)*2 + 1) * sizeof(char)));
            if (string->begin == old) {
                return;
            }
            (string->mem) *= 2;
        }
        ++idx;
    }
}

String* StringSlice(String* string, int begin_idx, int end_idx){
    char buff[end_idx - begin_idx + 1];
    for (int idx = 0; idx < end_idx - begin_idx; ++idx) {
        buff[idx] = string->begin[begin_idx + idx];
    }
    buff[end_idx - begin_idx] = 0;
    String* new_string = StringInit(buff);
    return new_string;
}

void StringPrint(String* string) {

    for (long unsigned int idx = 0; idx < string->size; ++idx) {
        printf("%c", string->begin[idx]);
    }
}

void StringDelete(String** string) {

    free((*string)->begin);
    free(*string);
    *string = NULL;
}
