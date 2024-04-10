#include <stdio.h>
#include "queue.h"
#include "bubble_sort.h"

void Operations() {
    printf("\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("a [var]: add an 'var' into the queue.\n");
    printf("r: remove (pop) last element from the queue.\n");
    printf("s: sort queue using bubble sorting method.\n");
    printf("p: print current queue.\n");
    printf("f: free the queue.\n");
    printf("o: re-show operations.\n");
    printf("q: quit.\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("\n\n");
}

int main() {
    udt q = udt_create();
    int element;
    char operation;
    
    Operations();
    
    while (operation != 'q') {
        scanf(" %c", &operation);
        if (operation == 'a') {
            scanf("%d", &element);
            udt_push(&q, element);
        } else if (operation == 'r') {
            int removed_item = udt_last(&q);
            udt_pop(&q);
            printf("last element was removed: %d\n", removed_item);
            if (udt_is_empty(&q)) {
                printf("queue is still empty.\n");
            }
        } else if (operation == 's') {
            if (udt_is_empty(&q)) {
                printf("queue is still empty.\n");
            } else if (!(udt_is_empty(&q))) {
                printf("queue before sorting:\n");
                udt_print(&q);
                BubbleSort(&q);
                printf("queue after sorting:\n");
                udt_print(&q);
            }
        } else if (operation == 'p') {
            if (udt_is_empty(&q)) {
                printf("queue is still empty.\n");
            }
            udt_print(&q);
        } else if (operation == 'f') {
            udt_free(&q);
            printf("now the queue is empty.\n");
        } else if (operation == 'o') {
            Operations();
        }
    }
    printf("\nExiting...");
    return 0;
}
