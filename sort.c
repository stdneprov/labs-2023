#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#include "sort.h"

void Sort(Stack** stack) {
    if (Size(*stack) <= 1) {
        return;
    }
    T pivot = Pop(*stack);
    Stack* stackLess = InitStack();
    Stack* stackMore = InitStack();
    while (!IsEmpty(*stack)) {
        T item = Pop(*stack);
        if (item >= pivot) {
            Push(stackMore, item);
        } else {
            Push(stackLess, item);
        }
    }
    Sort(&stackMore);
    Sort(&stackLess);
    Push(stackLess, pivot);
    Concatenation(stack, &stackLess);
    Concatenation(stack, &stackMore);
}