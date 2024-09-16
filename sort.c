#include "deq.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

void Swap(Deq* d, int count) {
    int el1 = DeqPopFront(d);
    for (int _ = 0; _ < (count - 1); _++) {
        DeqPushBack(d, DeqPopFront(d));
    }
    int el2 = DeqPopFront(d);
    DeqPushFront(d, el1);
    for (int _ = 0; _ < (count - 1); _++) {
        DeqPushFront(d, DeqPopBack(d));
    }
    DeqPushFront(d, el2);
}

int Part(Deq* d, int end) {
    int pivot = d->head->value;
    //printf("pivot = %d ", pivot);
    int count = 0;
    int size = d->size;
    //printf("OK9 ");
    DeqPushBack(d, DeqPopFront(d));
    int dublikat = 0;
    for (int _ = 0; _ < size - 1; _++) {
        //printf("%d ", d->head->value);
        if (d->head->value <= pivot) {
            if (d->head->value <= pivot) {
                dublikat++;
            }
            count++;
        }
        DeqPushBack(d, DeqPopFront(d));
    }
    //printf("count = %d ", count);
    //printf("OK3 ");
    if (count != 0) {
        Swap(d, count);
    }
    //printf("OK4 ");
    int pivotIndex = 0 + count;
    int i = 0;
    int j = end - 1;
    Deq f1 = DeqInit();
    Deq f2 = DeqInit();
    //printf("OK10 ");
    while (i < pivotIndex && j > pivotIndex) {
        //DeqPrint(d);
        //printf("\n");
        if (d->head->value <= pivot) {
            i++;
            DeqPushFront(&f1, DeqPopFront(d));
            //printf("OK11 %d ", i);
        } else if (d->tail->value > pivot) {
            j--;
            DeqPushFront(&f2, DeqPopBack(d));
        } else{
            int n = DeqPopBack(d);
            DeqPushBack(d, DeqPopFront(d));
            DeqPushFront(d, n);
            //DeqPushFront(&f1, DeqPopBack(d));
            //DeqPushFront(&f2, DeqPopFront(d));
            //printf("OK12 ");
        }
    }
    //printf("OK5 ");
    //DeqPrint(d);
    //printf("\n");
    //DeqPrint(&f1);
    //printf("\n");
    //DeqPrint(&f2);
    //printf("\n");
    //int k = 0;
    while(!(DeqIsEmpty(&f1))) {
        DeqPushFront(d, DeqPopFront(&f1));
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
    while(!(DeqIsEmpty(&f2))) {
        DeqPushBack(d, DeqPopFront(&f2));
        //k++;
        //if (k == 4) {
        //    break;
        //    printf("ujdyj");
        //}
    }
    //printf("p\n");
    //DeqPrint(d);
    //printf("p\n");
    //printf("%d (%d - %d)", pivotIndex, dublikat, end);
    if (dublikat == end - 1) {
        pivotIndex--;
    }
    //printf("%d ", pivotIndex);
    return pivotIndex;
}

void QuickSort(Deq* d, int end) {
    Deq q = DeqInit();
    Deq w = DeqInit();
    //printf("OK ");
    if (0 < end - 1) {
        //printf("%d\n", end);
        int pi = Part(d, end);
        if (pi == 0) {
            DeqPushFront(&w, DeqPopFront(d));
            while (!(DeqIsEmpty(d))) {
                DeqPushFront(&q, DeqPopBack(d));
            }
        } else {
            for (int _ = 0; _ <= pi; ++_) {
                DeqPushBack(&w, DeqPopFront(d));
            }
            while (!(DeqIsEmpty(d))) {
                DeqPushFront(&q, DeqPopBack(d));
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
    //printf("OK2");
    //DeqPrint(&w);
    //printf("\n");
    //DeqPrint(&q);
    //printf("\n");
    while(!(DeqIsEmpty(&w))) {
        DeqPushFront(d, DeqPopBack(&w));
    }
    while(!(DeqIsEmpty(&q))) {
        DeqPushBack(d, DeqPopFront(&q));
    }
}