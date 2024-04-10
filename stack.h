#ifndef _STACK_H_
#define _STACK_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "stack_item.h"

typedef struct Stack Stack;

struct Stack {
    Stack_Item* begin;
    Stack_Item* end;

    unsigned long int mem;
    unsigned long int size;
};

void Stack_create(Stack**);
bool Stack_is_empty(const Stack*);
void Stack_push(Stack*, Stack_Item);
void Stack_pop(Stack*);
void Stack_print(const Stack*);
size_t Stack_size(const Stack*);

Stack_Item Stack_top(Stack*);
void Stack_sys_print(const Stack*);
void Stack_clear(Stack*);
void Stack_delete(Stack**);

#endif