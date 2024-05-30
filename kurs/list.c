#include "list.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

size_t LNCreate(List *l, list_type v);

List *LCreate(void) {
    List *l = malloc(sizeof(List));
    if (l == NULL) {
        fprintf(stderr, "ERROR: buy more rum!\n");
        exit(EXIT_FAILURE);
    }
    l->capacity = MIN_CAPACITY;
    l->mem = malloc(l->capacity * sizeof(ListNode));
    if (!l->mem) {
        fprintf(stderr, "ERROR: buy more rum!\n");
        exit(EXIT_FAILURE);
    }
    l->head = 0;
    l->next_free = NULL;
    return l;
}

void LPrint(List *l) {
    Iterator it = IFirst(l);
    for (size_t i = 0; i < LLen(l); i++) {
        printf("%lu ", IGet(&it));
        INext(&it);
    }
    printf("\n");
}

size_t LLen(const List *l) {
    return l->size;
}

bool LIsEmpty(const List *l) {
    return l->size == 0;
}

void LPushBack(List *l, list_type v) {
    Iterator it = ILast(l);
    IInsert(&it, v);
    if (!l->head) {
        l->head = it.node;
    }
}

void LPushFront(List *l, list_type v) {
    Iterator it = ILast(l);
    IInsert(&it, v);
    l->head = it.node;
}

void LInsert(List *l, size_t i, list_type v) {
    if (i < 0 || i > LLen(l)) {
        fprintf(stderr,
                "ERROR: tried to remove an element at index %lu in a list with "
                "length %lu\n",
                i, LLen(l));
        exit(EXIT_FAILURE);
    }
    Iterator it = IAtPos(l, i);
    IInsert(IPrev(&it), v);
    if (i == 0) {
        l->head = it.node;
    }
}

void LRemove(List *l, size_t i) {
    if (i < 0 || i > LLen(l) - 1) {
        fprintf(stderr,
                "ERROR: tried to remove an element at index %lu in a list with "
                "length %lu\n",
                i, LLen(l));
        exit(EXIT_FAILURE);
    }
    Iterator it = IAtPos(l, i);
    IRemove(&it);
    if (i == 0) {
        l->head = it.node;
    }
}

void LRemoveInRange(List *l, list_type bottom, list_type top) {
    Iterator it = IFirst(l);
    size_t len = LLen(l);
    for (size_t i = 0; i < len; i++) {
        if (IGet(&it) >= bottom && IGet(&it) <= top) {
            if (it.node == l->head) {
                IRemove(&it);
                l->head = it.node;
            } else {
                IRemove(&it);
            }
        } else {
            INext(&it);
        }
    }
}

list_type LGet(List *l, size_t i) {
    if (i < 0 || i > LLen(l) - 1) {
        fprintf(stderr,
                "ERROR: tried to access an element at index %lu in a list with "
                "length %lu\n",
                i, LLen(l));
        exit(EXIT_FAILURE);
    }
    return l->mem[IAtPos(l, i).node].value;
}
void LSet(List *l, size_t i, list_type v) {
    if (i < 0 || i > LLen(l) - 1) {
        fprintf(stderr,
                "ERROR: tried to access an element at index %lu in a list with "
                "length %lu\n",
                i, LLen(l));
        exit(EXIT_FAILURE);
    }
    l->mem[IAtPos(l, i).node].value = v;
}

void LFree(List *l) {
    free(l->mem);
    while (l->next_free) {
        ANode *node = l->next_free;
        l->next_free = node->next;
        free(node);
    }
}

size_t LNCreate(List *l, list_type v) {
    if (l->size >= l->capacity - 1) { // first element - 0
        l->capacity += MIN_CAPACITY;
        l->mem = realloc(l->mem, l->capacity * sizeof(ListNode));
        if (l->mem == NULL) {
            fprintf(stderr, "ERROR: buy more rum!\n");
            exit(EXIT_FAILURE);
        }
    }
    if (l->next_free) {
        size_t res = l->next_free->node;
        l->mem[res].value = v;
        l->size++;

        ANode *to_free = l->next_free;
        l->next_free = l->next_free->next;
        free(to_free);

        return res;
    }
    l->size++;
    l->mem[l->size].value = v;
    return l->size;
}

Iterator IFirst(List *l) {
    Iterator it = {.l = l, .node = l->head};
    return it;
}
Iterator ILast(List *l) {
    Iterator it = {.l = l, .node = l->head};
    return *IPrev(&it);
}

Iterator IAtPos(List *l, size_t i) {
    Iterator it = IFirst(l);
    for (size_t j = 0; j < i; j++)
        INext(&it);
    return it;
}
// return the next element of an iterator
Iterator *INext(Iterator *it) {
    if (it->node == 0)
        return it;
    it->node = it->l->mem[it->node].next;
    return it;
}

// return the previous element of an iterator
Iterator *IPrev(Iterator *it) {
    if (it->node == 0)
        return it;
    it->node = it->l->mem[it->node].prev;
    return it;
}

// insert v as next element in the iterator and return it
Iterator *IInsert(Iterator *it, list_type v) {
    List *l = it->l;
    size_t ln = LNCreate(l, v);
    if (it->node == 0) {
        it->node = ln;
        l->mem[ln].next = ln;
        l->mem[ln].prev = ln;
        return it;
    }
    l->mem[ln].next = l->mem[it->node].next;
    l->mem[l->mem[it->node].next].prev = ln;

    l->mem[ln].prev = it->node;
    l->mem[it->node].next = ln;
    it->node = ln;
    return it;
}

// remove current element in the iterator and return the next one
Iterator *IRemove(Iterator *it) {
    List *l = it->l;
    if (it->node == 0) {
        return it;
    }
    l->mem[l->mem[it->node].prev].next = l->mem[it->node].next;
    l->mem[l->mem[it->node].next].prev = l->mem[it->node].prev;

    ANode *next = l->next_free;
    l->next_free = malloc(sizeof(ANode));
    if (!l->next_free) {
        fprintf(stderr, "ERROR: buy more rum!\n");
        exit(EXIT_FAILURE);
    }
    l->next_free->next = next;
    l->next_free->node = it->node;
    // size_t to_free = it->node;
    INext(it);
    l->size--;
    if (l->size == 0)
        it->node = 0;
    return it;
}

// get the value of the current
list_type IGet(Iterator *it) {
    return it->l->mem[it->node].value;
}
