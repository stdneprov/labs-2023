#include "list.h"

#include <stdio.h>
#include <stdlib.h>

ListNode *LNCreate(list_type v);

List *LCreate(void) {
    List *l = malloc(sizeof(List));
    if (l == NULL) {
        fprintf(stderr, "ERROR: buy more rum!\n");
        exit(EXIT_FAILURE);
    }
    l->head = NULL;
    return l;
}

void LPrint(const List *l) {
    Iterator it = IFirst(l);
    for (size_t i = 0; i < LLen(l); i++) {
        printf("%lu ", IGet(&it));
        INext(&it);
    }
    printf("\n");
}

size_t LLen(const List *l) {
    return l->len;
}

bool LIsEmpty(const List *l) {
    return l->len == 0;
}

void LPushBack(List *l, list_type v) {
    Iterator it = ILast(l);
    IInsert(&it, v);
    if (!l->head) {
        l->head = it.node;
    }
    l->len++;
}

void LPushFront(List *l, list_type v) {
    Iterator it = ILast(l);
    IInsert(&it, v);
    l->head = it.node;
    l->len++;
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
    l->len++;
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
    l->len--;
}

void LRemoveInRange(List *l, list_type bottom, list_type top) {
    Iterator it = IFirst(l);
    size_t len = LLen(l);
    for (size_t i = 0; i < len; i++) {
        if (IGet(&it) >= bottom && IGet(&it) <= top) {
            if (it.node == l->head) {
                l->head = l->head->next;
            }
            IRemove(&it);
            l->len--;
        } else {
            INext(&it);
        }
    }
}

list_type LGet(const List *l, size_t i) {
    if (i < 0 || i > LLen(l) - 1) {
        fprintf(stderr,
                "ERROR: tried to access an element at index %lu in a list with "
                "length %lu\n",
                i, LLen(l));
        exit(EXIT_FAILURE);
    }
    return IAtPos(l, i).node->value;
}
void LSet(List *l, size_t i, list_type v) {
    if (i < 0 || i > LLen(l) - 1) {
        fprintf(stderr,
                "ERROR: tried to access an element at index %lu in a list with "
                "length %lu\n",
                i, LLen(l));
        exit(EXIT_FAILURE);
    }
    IAtPos(l, i).node->value = v;
}

void LFree(List *l) {
    Iterator it = IFirst(l);
    for (size_t i = 0; i < LLen(l); i++) {
        IRemove(&it);
    }
}

ListNode *LNCreate(list_type v) {
    ListNode *ln = malloc(sizeof(ListNode));
    if (ln == NULL) {
        fprintf(stderr, "ERROR: buy more rum!\n");
        exit(EXIT_FAILURE);
    }
    ln->next = NULL;
    ln->prev = NULL;
    ln->value = v;
    return ln;
}

Iterator IFirst(const List *l) {
    Iterator it = {.node = l->head};
    return it;
}
Iterator ILast(const List *l) {
    Iterator it = {.node = l->head};
    return *IPrev(&it);
}

Iterator IAtPos(const List *l, size_t i) {
    Iterator it = IFirst(l);
    for (size_t j = 0; j < i; j++)
        INext(&it);
    return it;
}
// return the next element of an iterator
Iterator *INext(Iterator *it) {
    if (it->node == NULL)
        return it;
    it->node = it->node->next;
    return it;
}

// return the previous element of an iterator
Iterator *IPrev(Iterator *it) {
    if (it->node == NULL)
        return it;
    it->node = it->node->prev;
    return it;
}

// insert v as next element in the iterator and return it
Iterator *IInsert(Iterator *it, list_type v) {
    ListNode *ln = LNCreate(v);
    if (it->node == NULL) {
        it->node = ln;
        ln->next = ln;
        ln->prev = ln;
        return it;
    }
    ln->next = it->node->next;
    it->node->next->prev = ln;

    ln->prev = it->node;
    it->node->next = ln;
    it->node = ln;
    return it;
}

// remove current element in the iterator and return the next one
Iterator *IRemove(Iterator *it) {
    if (it->node == NULL) {
        return it;
    }
    it->node->prev->next = it->node->next;
    it->node->next->prev = it->node->prev;
    ListNode *to_free = it->node;
    INext(it);
    free(to_free);
    return it;
}

// get the value of the current
list_type IGet(Iterator *it) {
    return it->node->value;
}
