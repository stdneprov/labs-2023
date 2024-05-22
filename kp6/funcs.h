#ifndef __funcs_h__
#define __funcs_h__
#include <stdio.h>
#include "user.h"
void printfError(char *str, int err);
FILE *fileOpen(char *files[], int index, char *mode);
void checkErr(FILE *file);
#endif