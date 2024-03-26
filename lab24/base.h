#ifndef _BASE
#define _BASE
#include <stdio.h>
#include <stdlib.h>

#include "stack.h"
Token GetToken();
int GetPriority(char operator);
int IsLetter(char c);
int IsDigit(char c);
int gcd(int a, int b);
#endif