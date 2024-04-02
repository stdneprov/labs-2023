#ifndef __STACK__
#define __STACK__
#include "item.h"

typedef Item T;
typedef struct ItemS ItemS;

struct ItemS {
    T *value;
    ItemS *prev;
};

typedef struct Stack {
    ItemS *top;
} Stack;

void PushS (Stack* stack, T *value);
T *LookLastS (Stack* stack);
T *PopS (Stack* stack);

#endif