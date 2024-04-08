#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "queue.h"

Queue Find(Queue *q, Queue *qr) {
    if (QueueIsEmpty(q)) {
        printf("Exit");
        exit(-1);
    }
    int k1 = 0;
    int k2 = -1;
    Node* temp = q->first;
    int n;
    temp = temp->next;
    while (temp != NULL) {
        k1 += 1;
        if (temp->next == NULL) {
            printf("Такого элемента нет");
            exit(-1);
        }
        if ((temp->next->data < temp->data)) {
            n = temp->next->data;
            break;
        }
        temp = temp->next;
    }
    temp = q->first;
    temp = temp->next;
    for (int _ = 0; _ < k1 - 1; _++) {
        if (temp->data <= n) {
            k2 = _;
        }
        temp = temp->next;
    }
    temp = q->first;
    temp = temp->next;
    if (k2 == -1) {
        QueuePush(qr, n);
        for (int _ = 0; _ < q->size; _++) {
            if (!(_ == k1)) {
                QueuePush(qr, temp->data);
            }
            temp = temp->next;
        }
        return *qr;
    } else {
        for (int _ = 0; _ < k1; _++) {
            QueuePush(qr, temp->data);
            temp = temp->next;
            if (_ == k2) {
                QueuePush(qr, n);
            }
        }
        temp = temp->next;
        while (temp != NULL) {
            QueuePush(qr, temp->data);
            temp = temp->next;
        }
        return *qr;
    }
}