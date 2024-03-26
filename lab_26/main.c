#include <stdio.h>
#include "list.h"

typedef enum {
    STATE_FIND_DIGIT,
    STATE_SCAN
} state;

bool ShiftFirstMin(barrier_list *lst) {


    if (ListGetSize(lst) <= 1) {
        return false;
    }


    list_iter iter = ListIterBegin(lst);
    int prev_num = ListIterGet(&iter);
    ListIterMoveNext(&iter);


    for (; !ListIterEqual(iter, ListIterEnd(lst)); ListIterMoveNext(&iter)) {
        if (prev_num > ListIterGet(&iter)) {
            break;
        }
        else {
            prev_num = ListIterGet(&iter);
        }
    }
    if (ListIterEqual(iter, ListIterEnd(lst))) {
        return false;
    } 
    int shift_num = ListIterGet(&iter);
    ListIterRemove(&iter);
    ListIterMoveBack(&iter);
    for (; !ListIterEqual(iter, ListIterEnd(lst)); ListIterMoveBack(&iter)) {
        if (ListIterGet(&iter) < shift_num) {
            break;
        }
    }
    ListIterMoveNext(&iter);
    ListIterInsertBefore(&iter, shift_num);
    return true;
}

void Sort(barrier_list *lst) {
    while (ShiftFirstMin(lst));
}

bool IsSep(int ch) {
    return (('\t' <= ch && ch <= '\r') || ch == ' ');
}

int main() {
    barrier_list lst;
    ListInit(&lst);
    list_iter iter = ListIterBegin(&lst);
    int n = 0;
    int s;
    state st = STATE_FIND_DIGIT;
    int znak = 0;
    do {
        s = getchar();
        if (s == EOF || s == '\n' || s  == '-') {
            if (s == '-') {
                znak = 1;
            }
            continue;
        }
        if (IsSep(s) && st == STATE_SCAN) {
            if (znak == 1) {
                n = -n;
            }
            znak = 0;
            ListIterInsertBefore(&iter, n);
            n = 0;
            st = STATE_FIND_DIGIT;
        } else if (!IsSep(s) && (s <= 57 && s >= 48)) {
            n = n*10 + (s-'0');

            st = STATE_SCAN;
        } else if (IsSep(s)) {
            znak = 0;
        }
    }
    while (s != EOF && s != '\n');
    if (st == STATE_SCAN) {
        if (znak == 1) {
                n = -n;
                znak = 0;
        }
        ListIterInsertBefore(&iter, n);
    }
    Sort(&lst);
    for (iter = ListIterBegin(&lst); !ListIterEqual(iter, ListIterEnd(&lst)); ListIterMoveNext(&iter)) {
        printf("%d ", ListIterGet(&iter));
    }
    printf("\n");
    ListDestroy(&lst);
    return 0;
}
