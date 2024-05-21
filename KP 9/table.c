#include "table.h"
#include "sort.h"



Table* CreateTable() {
    Table* tb = (Table*)malloc(sizeof(Table));
    if(!tb) {
        return NULL;
    } 
    item* data = (item*)malloc(MIN_CAPACITY * sizeof(item));
    if(!data) {
        free(tb);
        return NULL;
    }
    tb->capacity = MIN_CAPACITY;
    tb->rows = data;
    tb->size = 0;
    return tb;
}

bool Buffer(Table* t) {
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
        printf("%2d | %10s | %s\n", i, t->rows[i].key, t->rows[i].val);
}

void Destroy(Table* t) {
    free(t->rows);
    free(t);
}

int Compare(char* a, char* b) {
    //-1 - меньше 0 - равны 1 - больше
    int i = 0;
    int add = 0;
    int mul = 1;
    int countA = 0;
    int countB = 0;
    if (a[0] == '-' && b[0] != '-') {
        return -1;
    } else if (b[0] == '-' && a[0] != '-') {
        return 1;
    } else if (b[0] == '-' && a[0] == '-') {
        add = 1;
        mul = -1;
    }
    while (i < 9) {
        if (a[i] <= '9' && a[i] >= '0') {
            countA += 1;
        }
        if (b[i] <= '9' && b[i] >= '0') {
            countB += 1;
        }
        i += 1;
    }

    if (countA > countB) {
        return 1 * mul;
    } else if (countA < countB) {
        return -1 * mul;
    }
    
    i = 0 + add;
    while (true && i < 9) {
        if (a[i] == 0 && b[i] == 0) {
            return 0;
        }
        if (a[i] > b[i]) {
            if (a[i] <= '9' && a[i] >= '0') {
                return 1 * mul;
            } else {
                return 1;
            }
        } else if (a[i] < b[i]) {
            if (a[i] <= '9' && a[i] >= '0') {
                return -1 * mul;
            } else {
                return -1;
            }
        } else {
            i += 1;
        }
    }
    return 0;
}

int Search(Table* t, char* k) {
    int l = 0;
    int r = t->size - 1;
    int result = -1;
    while(l <= r) {
        int x = (l + r) >> 1;
        int c;
        if (Compare(t->rows[x].key, k) == 0) {
            c = 0;
        } else if (Compare(t->rows[x].key, k) == 1) {
            c = 1;
        } else {
            c = -1;
        }
        if(c == 0) {
            result = x;
            r = x - 1;
        } else if(c > 0)
            r = x - 1;
        else 
            l = x + 1;
    }
    return result;
}