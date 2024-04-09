#include "item.h"


#define MIN_CAPACITY 14

int KeyCMP(long int key1, long int key2) {
    return key1 - key2;
}

Table* CreateTable() {
    Table* tb = (Table*)malloc(sizeof(Table));
    if(!tb) {
        return NULL;
    } 
    item* buff = (item*)malloc(MIN_CAPACITY * sizeof(item));
    if(!buff) {
        free(tb);
        return NULL;
    }
    tb->capacity = MIN_CAPACITY;
    tb->rows = buff;
    tb->size = 0;
    return tb;
}

// Expands table buffer if necessary
static bool Buffer(Table* t) {
    if(t->size < t->capacity)
        return true;
    int new_cap = 2 * t->capacity;
    item* tmp = (item*)realloc(t->rows, sizeof(item) * new_cap);
    if(!tmp) {
        return false; 
    }
    t->capacity = new_cap;
    t->rows = tmp;
    return true;
}

bool Add(Table* t, item r) {
    if(!Buffer(t))
        return false; 
    t->rows[t->size] = r;
    t->size++;
    return true;
}

void Print(Table* t) {
    for(int i = 0; i < t->size; ++i)
        printf("%2d | %6ld | %s\n", i, t->rows[i].key, t->rows[i].val);
}

void Destroy(Table* t) {
    free(t->rows);
    free(t);
}

int Search(Table* t, long int k) {
    int l = 0;
    int r = t->size - 1;
    int result = -1;
    while(l <= r) {
        int x = (l + r) >> 1;
        int cmp;
        if (t->rows[x].key == k) {
            cmp = 0;
        } else if (t->rows[x].key > k) {
            cmp = 1;
        } else {
            cmp = -1;
        }
        // int cmp = strcmp(t->rows[x].key, k);
        if(cmp == 0) {
            result = x;
            r = x - 1;
        } else if(cmp > 0)
            r = x - 1;
        else 
            l = x + 1;
    }
    return result;
}