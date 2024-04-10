#ifndef _STACK_ITEM_H_
#define _STACK_ITEM_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Stack_Item Stack_Item;

struct Stack_Item {
    int value;
};

Stack_Item Data_to_Stack_Item(int);
void Stack_Item_assign(Stack_Item*, Stack_Item);
void Stack_Item_print(const Stack_Item*);
bool Stack_Item_is_greater(const Stack_Item, const Stack_Item);

#endif