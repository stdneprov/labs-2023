#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "stack.h"
#include "stack_module.h"

void Stack_reverse_migrate(Stack* target, Stack* source) {
    while (!Stack_is_empty(source)) {
        Stack_push(target, Stack_top(source));
        Stack_pop(source);
    }
}

void Stack_concatenate(Stack* stack, Stack** extension) {
    Stack* buff;
    Stack_create(&buff);

    Stack_reverse_migrate(buff, *extension);

    Stack_delete(extension);
    
    Stack_reverse_migrate(stack, buff);

    Stack_delete(&buff);
}

void Stack_qsort(Stack* stack) {
    if (Stack_size(stack) <= 1) {
        return;
    }

    Stack_Item base = Stack_top(stack);
    Stack_pop(stack);

    Stack* le;
    Stack* gr_or_eq;
    Stack_create(&le);
    Stack_create(&gr_or_eq);
    Stack_push(gr_or_eq, base);

    while (!Stack_is_empty(stack)) {
        
        if (Stack_Item_is_greater(Stack_top(stack), base)) {
            Stack_push(gr_or_eq, Stack_top(stack));
        } else {
            Stack_push(le, Stack_top(stack));
        }

        Stack_pop(stack);
    }

        Stack_qsort(gr_or_eq);

    if (!Stack_is_empty(le)) {
        Stack_reverse_migrate(stack, le);
        Stack_qsort(stack);
    }

    Stack_delete(&le);

    Stack_concatenate(stack, &gr_or_eq);
}
