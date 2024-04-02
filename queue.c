#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

void PushQ (Queue* queue, T *value) {
    if (queue->tail != NULL) {
        ItemQ* newItem = (ItemQ*)malloc(sizeof(ItemQ));
        newItem->next = NULL;
        newItem->value = value;
        queue->tail->next = newItem;
        queue->tail = newItem;
    } else {
        ItemQ* newItem = (ItemQ*)malloc(sizeof(ItemQ));
        newItem->next = NULL;
        newItem->value = value;
        queue->tail = newItem;
        queue->head = newItem;
    }
}

T *LookLastQ(Queue *queue)
{
    return queue->head->value;
}

T *PopQ (Queue* queue) {
    if (queue->head != NULL) {
        T *value = queue->head->value;
        ItemQ *oldHead = queue->head;
        queue->head = queue->head->next;
        free(oldHead);
        return value;
    } else {
        return NULL;
    }
}