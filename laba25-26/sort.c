#include <stdio.h>
#include "stack.h"
#include "sort.h"

void Sort(Stack** stack) {
    if (Size(*stack) <= 1) {
        return;
    }

    Stack* sortedStack = InitStack();
    Stack* tempStack = InitStack();

    while (!IsEmpty(*stack)) {
        T maxItem = ExtractMax(*stack, tempStack);
        Push(sortedStack, maxItem);

        
        while (!IsEmpty(tempStack)) {
            Push(*stack, Pop(tempStack));
        }
    }

    DelStack(stack); 
    *stack = sortedStack; 
    DelStack(&tempStack); 
}
