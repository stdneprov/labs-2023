#include "stack.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

void Swap(Stack* stk, int count) {
    Stack stk1 = StackInit();
    while (!(StackIsEmpty(stk))) {
        StackPush(&stk1, StackPop(stk)); 
    }
    int a1 = StackPop(&stk1);
    for (int _ = 0; _ < (count - 1); _++) {
        StackPush(stk, StackPop(&stk1));
    }
    int a2 = StackPop(&stk1);
    StackPush(&stk1, a1);
    for (int _ = 0; _ < (count - 1); _++) {
        StackPush(&stk1, StackPop(stk));
    }
    StackPush(&stk1, a2);
    while (!(StackIsEmpty(&stk1))) {
        StackPush(stk, StackPop(&stk1)); 
    }
    StackFree(&stk1);
}

void StackCopy(Stack* stk, Stack* stk1) {
    Stack q = StackInit();
    int a;
    while (!(StackIsEmpty(stk))) {
        a = StackPop(stk);
        StackPush(&q, a);
        StackPush(stk1, a);
    }
    while (!(StackIsEmpty(&q))) {
        StackPush(stk, StackPop(&q));
    }
    StackFree(&q);
}

int Sort1(Stack* stk, int end) {
    Stack stk1 = StackInit();
    while (!(StackIsEmpty(stk))) {
        StackPush(&stk1, StackPop(stk)); 
    }
    int pivot = stk1.top->value;
    //printf("pivot = %d ", pivot);
    int count = 0;
    //int size = d->size;
    //printf("OK9 ");
    StackPush(stk, StackPop(&stk1));
    //int dublikat = 0;
    while (!(StackIsEmpty(&stk1))) {
        //printf("%d ", d->head->value);
        if (stk1.top->value <= pivot) {
            //dublikat++;
            count++;
        }
        StackPush(stk, StackPop(&stk1));
    }
    //printf("count = %d ", count);
    //printf("OK3 ");
    if (count != 0) {
        Swap(stk, count);
    }
    //printf("OK4 ");
    StackCopy(stk, &stk1);
    int pivotIndex = count;
    int i = 0;
    int j = end - 1;
    Stack f1 = StackInit();
    Stack f2 = StackInit();
    //printf("%d\n ", pivot);
    //StackPrint(&stk1);
    //printf("\n");
    //StackPrint(stk);
    //printf("\n");
    while (i < pivotIndex && j > pivotIndex) {
        //DeqPrint(d);
        //printf("\n");
        if (stk1.top->value <= pivot) {
            i++;
            //printf("OK11 %d ", stk1.top->value);
            StackPush(&f1, StackPop(&stk1));
        } else if (stk->top->value > pivot) {
            j--;
            StackPush(&f2, StackPop(stk));
            //printf(" g ");
        } else {
           // printf("OK12 ");
            int n = StackPop(&stk1);
            StackPush(&stk1, StackPop(stk));
            StackPush(stk, n);
            //DeqPushFront(&f1, DeqPopBack(d));
            //DeqPushFront(&f2, DeqPopFront(d));
        }
    }
    while (i < pivotIndex) {
        StackPush(&f1, StackPop(&stk1));
        i++;
    }
    while (j > pivotIndex) {
        StackPush(&f2, StackPop(stk));
        j--;
    }
    StackPush(&f1, StackPop(&stk1));
    //printf("hay");
    //printf("OK5 ");
    //DeqPrint(d);
    //printf("\n");
    //DeqPrint(&f1);
    //printf("\n");
    //DeqPrint(&f2);
    //printf("\n");
    //int k = 0;
    while(!(StackIsEmpty(&f1))) {
        StackPush(&f2, StackPop(&f1));
        //DeqPrint(&f1);
        //++k;
        //if (k == 4) {
        //    break;
        //}
        //printf("\n");
    }
    //DeqPrint(d);
    //printf("l\n");
    //k = 0;
    //printf("p\n");
    //DeqPrint(d);
    //printf("p\n");
    //printf("%d (%d - %d)", pivotIndex, dublikat, end);
    while(!(StackIsEmpty(stk))) {
        StackPop(stk);
    }
    while(!(StackIsEmpty(&f2))) {
        StackPush(stk, StackPop(&f2));
    }
    if (count == end - 1) {
        pivotIndex--;
    }
    //StackPrint(stk);
    StackFree(&stk1);
    StackFree(&f1);
    StackFree(&f2);
    //printf("%d ", pivotIndex);
    return pivotIndex;
}

void QuickSort(Stack* stk, int end) {
    Stack q = StackInit();
    Stack w = StackInit();
    Stack hell = StackInit();
    //printf("OK ");
    if (0 < end - 1) {
        int pi = Sort1(stk, end);
        while (!(StackIsEmpty(stk))) {
            //printf("lol");
            StackPush(&hell, StackPop(stk));
        }
        //StackPrint(&hell);
        if (pi == 0) {
            StackPush(&w, StackPop(&hell));
            while (!(StackIsEmpty(&hell))) {
                StackPush(&q, StackPop(&hell));
            }
        } else {
            //printf("%d\n", pi);
            for (int _ = 0; _ <= pi; _++) {
                StackPush(&w, StackPop(&hell));
            }
            while (!(StackIsEmpty(&hell))) {
                StackPush(&q, StackPop(&hell));
            }
        }
        //printf("OK8 ");
        //DeqPrint(&w);
        //printf("\n");
        //printf("//");
        //DeqPrint(&q);
        //printf("//");
        //printf("\n");
        QuickSort(&w, w.size);
        QuickSort(&q, q.size);
    }
    while (!(StackIsEmpty(&w))) {
        StackPush(&hell, StackPop(&w));
    }
    //printf("OK2");
    //DeqPrint(&w);
    //printf("\n");
    //DeqPrint(&q);
    //printf("\n");
    while(!(StackIsEmpty(&hell))) {
        StackPush(stk, StackPop(&hell));
    }
    while (!(StackIsEmpty(&q))) {
        StackPush(&hell, StackPop(&q));
    }
    while(!(StackIsEmpty(&hell))) {
        StackPush(stk, StackPop(&hell));
    }
    StackFree(&hell);
    StackFree(&w);
    StackFree(&q);
}
