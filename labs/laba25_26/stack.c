#include "stack.h"
#include <stdio.h>

stack* stack_create(size_t c) {
    stack* s = malloc(sizeof(stack));
    s->capacity = c;
    s->size = 0;
    s->data = malloc(sizeof(int) * s->capacity);
    // (*s).data
}

void stack_free(stack* s) {
    free(s->data);
    free(s);
}

bool stack_is_empty(const stack* s) {
    return s->size == 0;
}

void stack_push(stack* s, int value) {
    if (s->size < s->capacity) {
        s->data[s->size] = value;
        ++s->size;
        return;
    }
    int* t = malloc(sizeof(int) * (s->capacity + 1) * 2);
    for (size_t i = 0; i < s->size; ++i) {
        t[i] = s->data[i];
    }
    t[s->size] = value;
    free(s->data);
    s->data = t;
    ++s->size;
    s->capacity = (s->capacity + 1) * 2;
}

int stack_pop(stack* s) {
    int x = s->data[s->size - 1];
    --s->size;
    return x;
}

int stack_top(const stack* s) {
    return s->data[s->size - 1];
}

void stack_print(const stack* s) {
    printf("Size: %ld, capacity: %ld, data: ", s->size, s->capacity);
    for (size_t i = 0; i < s->size; ++i) {
        printf("%d ", s->data[i]);
    }
    printf("\n");
}

void stack_merge(stack* a, stack* b, stack* c) {
    stack* ms = stack_create(0);
    while (!stack_is_empty(a) && !stack_is_empty(b)) {
        if (stack_top(a) < stack_top(b) ) {
            stack_push(ms, stack_pop(b));
        } else {
           stack_push(ms, stack_pop(a));
        }
    }
    while (!stack_is_empty(a)) {
        stack_push(ms, stack_pop(a));
    }
    while (!stack_is_empty(b)) {
        stack_push(ms, stack_pop(b));
    }
    while (!stack_is_empty(ms)) {
        stack_push(c, stack_pop(ms));
    }
    stack_free(ms);
}

void stack_sort(stack* s) {
    stack* a = stack_create(0);
    stack* b = stack_create(0);
    while (s->size != 0) {
        if (s->size % 2 == 0) {
            stack_push(a, stack_pop(s));
        } else {
           stack_push(b, stack_pop(s));
        }
    }
    if (a->size > 1) {
        stack_sort(a);
    }
    if (b->size > 1) {
        stack_sort(b);
    }
    stack_merge(a, b, s);
    stack_free(a);
    stack_free(b);
}

