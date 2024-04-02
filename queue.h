#ifndef __QUEUE__
#define __QUEUE__
#include "item.h"

typedef Item T;
typedef struct ItemQ ItemQ;

struct ItemQ {
    T *value;
    ItemQ *next;
};

typedef struct Queue {
    ItemQ *tail;
    ItemQ *head;
} Queue;

void PushQ (Queue* queue, T *value);
T *LookLastQ (Queue* queue);
T *PopQ (Queue* queue);

#endif