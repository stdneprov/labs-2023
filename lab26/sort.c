#include <stdio.h>
#include "sort.h"
#include "stack.h"


void StackMerge(Stack *res, Stack *a, Stack *b) {
    long long int i = 0;
    long long int j = 0;
    for (i = 0; i < a->count; i ++) {
        while ((j < b->count) && (a->buff[i] > b->buff[j])) {
            StackPush(res, b->buff[j]);
            j++;
        }
        StackPush(res, a->buff[i]);
    }
    while (j < b->count) {
        StackPush(res, b->buff[j]);
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