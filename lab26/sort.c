#include <stdio.h>
#include "sort.h"
#include "stack.h"


void StackMerge(Stack *res, Stack *a, Stack *b) {
    long long int i = 0;
    long long int j = 0;
    while (1) {
        if ((i >= a->count) || (j >= b->count)) {
            break;
        }
        if (StackGetElement(a, i) < StackGetElement(b, j)) {
            StackPush(res, StackGetElement(b, j));
            j++;
        } else {
            StackPush(res, StackGetElement(a, i));
            i++;
        }
    }
    while (i < a->count) {
        StackPush(res, StackGetElement(a, i));
        i++;
    }
    while (j < b->count) {
        StackPush(res, StackGetElement(b, j));
        j++;
    }
}

void StackSort(Stack *stk) {
    if (stk->count <= 1)
        return;
    Stack l = StackInit();
    Stack r = StackInit();
    long long int i;
    for (i = 0; i < stk->count / 2; i++) {
        StackPush(&l, stk->buff[i]);
    }
    for (i = stk->count / 2 ; i < stk->count; i++) {
        StackPush(&r, stk->buff[i]);
    }
    stk->count = 0;
    StackSort(&l);
    StackSort(&r);
    StackMerge(stk, &l, &r);
}