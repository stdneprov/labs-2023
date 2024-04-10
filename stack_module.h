#ifndef _STACK_MODULE_H_
#define _STACK_MODULE_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "stack.h"

void Stack_reverse_migrate(Stack*, Stack*);
void Stack_concatenate(Stack*, Stack**);
void Stack_qsort(Stack*);

#endif
