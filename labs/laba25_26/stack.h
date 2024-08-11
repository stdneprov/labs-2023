#ifndef _STACK_H_
#define _STACK_H_

#include <stdbool.h>
#include <stdlib.h>

typedef struct {
    int* data;
    size_t size;
    size_t capacity;
} stack;

stack*  stack_create(size_t c);
void    stack_free(stack* s);
bool    stack_is_empty(const stack* s);
void    stack_push(stack* s, int value);
int     stack_pop(stack* s);
int     stack_top(const stack* s);
void    stack_print(const stack* s);
void    stack_merge(stack* a, stack* b, stack* c);
void    stack_sort(stack* s);

#endif // _STACK_H_