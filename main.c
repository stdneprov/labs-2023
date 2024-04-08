#include <stdio.h>
#include "queue.h"

void ShowMenu() {
    printf("\n");
    printf("------------------\n");
    printf("a v: add element v\n");
    printf("d: pop last element\n");
    printf("p: print\n");
    printf("s: sort queue\n");
    printf("q: quit\n");
    printf("------------------\n");
    printf("\n");
}

int main() {
    Queue q = QueueInit();
    char command;
    int a;
    printf("Press 'm' to show menu\n");
    do {
        scanf("%c", &command);
        if (command == 'm') {
            ShowMenu();
        } else if (command == 'a') {
            scanf("%d", &a);
            QueuePush(&q, a);
            QueuePrint(&q);
        } else if (command == 'd') {
            QueuePop(&q);
            if (QueueIsEmpty(&q)) {
                printf("Empty");
            }
            QueuePrint(&q);
        } else if (command == 'p') {
            if (QueueIsEmpty(&q)) {
                printf("Empty");
            }
            QueuePrint(&q);
        } else if (command == 's') {
            InsertionSort(&q);
            printf("Sorted:\n");
            if (QueueIsEmpty(&q)) {
                printf("Empty");
            }
            QueuePrint(&q);
        }
    } while (command != 'q');
    return 0;
}