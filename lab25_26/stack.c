#include <stdio.h>
#include <stdlib.h>

#include "stack.h"

stack *stack_create(void) {
    stack *res = malloc(sizeof(stack));
    res->ptr = 0;
    res->size = 0;
    res->capacity = 0;
    return res;
}

bool stack_is_empty(const stack *s) {
    return s->size == 0;
}

size_t stack_size(const stack *s) {
    return s->size;
}

void stack_print(const stack *s) {
    for (size_t i = 0; i < s->size - 1; i++) {
        printf("%i, ", s->ptr[i]);
    }
    printf("%d\n", s->ptr[s->size - 1]);
}

void stack_push_back(stack *s, const STACK_T val) {
    if (s->ptr == NULL) {
        s->ptr = malloc(sizeof(STACK_T));
        if (s->ptr == NULL) {
            printf("ERROR: not enough memory");
            exit(EXIT_FAILURE);
        }
        s->capacity = 1;
    }
    if (s->size + 1 > s->capacity) {
        STACK_T *tmp = realloc(s->ptr, s->capacity * 2 * sizeof(STACK_T));
        if (tmp == NULL) {
            printf("ERROR: not enough memory");
            exit(EXIT_FAILURE);
        }
        s->capacity *= 2;
        s->ptr = tmp;
    }
    s->ptr[s->size++] = val;
}

void stack_push_front(stack *s, const STACK_T val) {
    stack_push_back(s, 0);
    for (int i = s->size - 1; i > 0; i--) {
        s->ptr[i] = s->ptr[i - 1];
    }
    s->ptr[0] = val;
}

void stack_pop_back(stack *s) {
    if (s->size == 0)
        return;
    if (--s->size <= s->capacity / 4) {
        STACK_T *tmp = malloc(s->capacity / 4 * sizeof(STACK_T));
        if (tmp == NULL) {
            printf("ERROR: not enough memory");
            exit(EXIT_FAILURE);
        }
        s->capacity /= 4;
        s->ptr = tmp;
    }
}

STACK_T *stack_back(const stack *s) {
    return &s->ptr[s->size - 1];
}

STACK_T *stack_get(const stack *s, size_t i) {
    if (i < 0 || i >= s->size)
        return NULL;
    return &s->ptr[i];
}

void stack_merge(stack *res, const stack *a, const stack *b) {
    size_t j = 0;
    for (size_t i = 0; i < stack_size(a); i++) {
        while (j < stack_size(b) && *stack_get(b, j) < *stack_get(a, i)) {
            stack_push_back(res, *stack_get(b, j));
            j++;
        }
        stack_push_back(res, *stack_get(a, i));
    }
    while (j < stack_size(b)) {
        stack_push_back(res, *stack_get(b, j));
        j++;
    }
}

void stack_free(stack *s) {
    free(s->ptr);
    free(s);
}

void stack_sort(stack *s) {
    if (s->size <= 1)
        return;
    stack *l = stack_create();
    stack *r = stack_create();
    size_t i;
    for (i = 0; i < s->size / 2; i++) {
        stack_push_back(l, s->ptr[i]);
    }
    for (; i < s->size; i++) {
        stack_push_back(r, s->ptr[i]);
    }

    s->size = 0;
    stack_sort(l);
    stack_sort(r);
    stack_merge(s, l, r);
    stack_free(l);
    stack_free(r);
}
