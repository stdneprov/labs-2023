#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "queue.h"

void Find(Queue *q) {
    //if (QueueIsEmpty(q)) {
    //    printf("Exit");
    //    exit(-1);
    //}
    Queue qt1;
    Queue *qr = &qt1;
    Create(qr);
    Queue qt2;
    Queue *qt = &qt2;
    Create(qt);
    int n1, n2;
    while(!(QueueIsEmpty(q))) {
        int d = 0;
        if (QueueIsEmpty(qr) && QueueIsEmpty(qt)) {
            n1 = QueuePop(q);
            QueuePush(qr, n1);
        } else if (QueueIsEmpty(qr)) {
            //printf("OK");
            while (!(QueueIsEmpty(qt))) {
                QueuePush(qr, QueuePop(qt));
            }
            //printf("OKo");
        }
        //printf("\nTTT\n");
        n1 = qr->first->data;
        //printf("%d\n", n1);
        n2 = QueuePop(q);
        while(!(QueueIsEmpty(qr))) {
            if (n1 > n2) {
                d = 1;
                QueuePush(qt, n2);
                while(!(QueueIsEmpty(qr))) {
                    //printf("OKey");
                    QueuePush(qt, QueuePop(qr));
                }
                break;
            } else {
                QueuePush(qt, QueuePop(qr));
                if (qr->first != NULL)
                    {n1 = qr->first->data;}
            }
        }
        if (d == 0) {
            QueuePush(qt, n2);
        }
    }
    while(!(QueueIsEmpty(qt))) {
        QueuePush(q, QueuePop(qt));
    }
}