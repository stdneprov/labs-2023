#include "list.h"
#define K_SIZE 2
#define INITIAL_SIZE 8

static int GetNext(list_iter *it) {
    return it->lst->buf[it->cur].pn ^ it->prev;
}

static int GetPrevBefore(list_iter *it) {
    return it->cur ^ it->lst->buf[it->prev].pn;
}

static int PopEmpty(barrier_list *lst) {
    int res = lst->first_empty;
    lst->first_empty = lst->buf[res].pn ^ lst->last_add;
    lst->last_add = res;
    return res;
}

static bool GrowBuffer(barrier_list *l) {
    int new_size = l->pool_size * K_SIZE;
    Listel *new_buf = realloc(l->buf, (new_size+1) * sizeof(Listel));
    if (new_buf == NULL) {
        return false;
    } 
    l->buf = new_buf;
    int old_barrier = l->barrier;
    l->barrier = new_size;
    for (int i = l->pool_size+1; i < new_size; ++i) {
        l->buf[i].pn = (i-1)^(i+1);
    }
    l->buf[l->barrier].pn = l->buf[old_barrier].pn;
    l->buf[old_barrier].pn = l->last_add ^ (old_barrier + 1);
    l->first_empty = old_barrier;
    int last = l->buf[l->barrier].pn ^ l->first;
    l->buf[last].pn = l->buf[last].pn ^ old_barrier ^ l->barrier;
    l->buf[l->first].pn = l->buf[l->first].pn ^ old_barrier ^ l->barrier;
    l->pool_size = new_size;
    return true;
}

bool ListInit(barrier_list *l) {
    l->buf = malloc((INITIAL_SIZE+1) * sizeof(Listel));
    if (l->buf == NULL) {
        return false;
    }
    l->pool_size = INITIAL_SIZE;
    l->barrier = INITIAL_SIZE;
    l->first = l->barrier;
    l->size = 0;
    for (int i = 1; i < l->pool_size; ++i) {
        l->buf[i].pn = (i-1)^(i+1);
    }
    l->buf[0].pn = 1^l->barrier;
    l->buf[l->barrier].pn = 0;
    l->first_empty = 0;
    l->last_add = l->barrier;
    return true;
}
void ListDestroy(barrier_list *l) {
    list_iter it = ListIterBegin(l);
    while (!ListIterEqual(it, ListIterEnd(l))) {
        ListIterRemove(&it);
    }
}
int ListGetSize(barrier_list *l) {
    return l->size;
}

list_iter ListIterBegin(barrier_list *l) {
    list_iter it;
    it.lst = l;
    it.prev = l->barrier;
    it.cur = l->first;
    return it;
}

list_iter ListIterEnd(barrier_list *l) {
    list_iter it;
    it.lst = l;
    it.cur = l->barrier;
    it.prev = l->buf[l->barrier].pn ^ l->first;
    return it;
}

bool ListIterEqual(list_iter it1, list_iter it2) {
    return it1.prev == it2.prev && it1.cur == it2.cur && it1.lst == it2.lst;
}

void ListIterMoveNext(list_iter *it) {
    int next = GetNext(it);
    it->prev = it->cur;
    it->cur = next;
}

void ListIterMoveBack(list_iter *it) {
    int prev_before = GetPrevBefore(it);
    it->cur = it->prev;
    it->prev = prev_before;
}

int ListIterGet(list_iter *it) {
    return it->lst->buf[it->cur].val;
}

void ListIterSet(list_iter *it, int val) {
    it->lst->buf[it->cur].val = val;
}

bool ListIterInsertBefore(list_iter *it, int val) {
    if (it->lst->size >= it->lst->pool_size) {
        int old_barrier = it->lst->barrier;
        if (!GrowBuffer(it->lst)) {
            return false;
        } 
        if (it->cur == old_barrier) it->cur = it->lst->barrier;
        if (it->prev == old_barrier) it->prev = it->lst->barrier;
    }
    int new_id = PopEmpty(it->lst);
    Listel* new_el = &it->lst->buf[new_id];
    new_el->pn = it->cur ^ it->prev;
    new_el->val = val;
    int next = GetNext(it);
    if (ListGetSize(it->lst) > 0) {
        it->lst->buf[it->prev].pn = GetPrevBefore(it) ^ new_id;
        it->lst->buf[it->cur].pn = new_id ^ next;
    }
    it->prev = new_id;
    it->lst->size++;
    if (it->cur == it->lst->first) {
        it->lst->first = new_id;
    }
    return true;
}

void ListIterRemove(list_iter *it) {
    int next = GetNext(it);
    if (ListGetSize(it->lst) > 1) {
        it->lst->buf[it->prev].pn = GetPrevBefore(it) ^ next;
        it->lst->buf[next].pn = it->lst->buf[next].pn ^ it->cur ^ it->prev;
    }
    if (it->lst->first == it->cur) {
        it->lst->first = next;
    }
    if (it->lst->first_empty != it->lst->barrier) {
        it->lst->buf[it->lst->first_empty].pn =
            it->lst->buf[it->lst->first_empty].pn ^ it->lst->last_add ^ it->cur;
    }

    it->lst->buf[it->cur].pn = it->lst->last_add ^ it->lst->first_empty;
    it->lst->first_empty = it->cur;
    it->cur = next;
    it->lst->size--;
}

list_iter ListIterFind(barrier_list *l, int val) {
    list_iter iter = ListIterBegin(l);
    for (;!ListIterEqual(iter, ListIterEnd(l)); ListIterMoveNext(&iter)) {
        if (ListIterGet(&iter) == val) {
            break;
        } 
    }
    return iter;
}
