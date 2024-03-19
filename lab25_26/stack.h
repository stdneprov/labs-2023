#ifndef _STACK_H_
#define _STACK_H_

#ifndef STACK_INIT_SIZE
#define STACK_INIT_SIZE 0
#endif

#include <stdbool.h>
#include <stddef.h>

typedef int STACK_T;

typedef int value_type;

typedef struct {
    STACK_T *ptr;
    size_t size;
    size_t capacity;
} stack;

stack *stack_create(void);
bool stack_is_empty(const stack *);
size_t stack_size(const stack *);
void stack_print(const stack *);
void stack_push_back(stack *, const STACK_T);
void stack_push_front(stack *, const STACK_T);
void stack_pop_back(stack *);
STACK_T *stack_back(const stack *);
STACK_T *stack_get(const stack *, size_t);
void stack_merge(stack *, const stack *, const stack *);
void stack_sort(stack *);
void stack_free(stack *);

#endif
