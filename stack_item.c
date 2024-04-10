#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "stack_item.h"

Stack_Item Data_to_Stack_Item(int val) {
    Stack_Item item;
    item.value = val;
    return item;
}

void Stack_Item_print(const Stack_Item* item) {
    printf("%d ", item->value);
}

bool Stack_Item_is_greater(const Stack_Item lval, const Stack_Item rval) {
    return (lval.value > rval.value);
}
