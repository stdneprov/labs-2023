#include <stdio.h>

#include "list.h"

void print_help(void) {
    printf("p [v]:\tpush value <v> to the back of the list\n");
    printf("P [v]:\tpush value <v> to the front of the list\n");
    printf("i [i v]:\tinsert value <v> on position <i>\n");
    printf("s [i v]:\tset value <v> on position <i>\n");
    printf("g [i]:\tget value on position <i>\n");
    printf("r [i]:\t remove value on position <i>\n");
    printf("R [a, b]:\t remove all values in range [<a>, <b>]\n");
    printf("d: print\n");
    printf("q: quit\n");
    printf("h: print help\n");
}

int main(void) {
    List *l = LCreate();
    char c;
    size_t a, b;
    printf("> ");
    while (scanf("%c", &c) != EOF) {
        switch (c) {
        case '\n':
            continue;
        case 'p':
            scanf("%lu", &a);
            LPushBack(l, a);
            break;
        case 'P':
            scanf("%lu", &a);
            LPushFront(l, a);
            break;
        case 'i':
            scanf("%lu %lu", &a, &b);
            LInsert(l, a, b);
            break;
        case 's':
            scanf("%lu %lu", &a, &b);
            LSet(l, a, b);
            break;
        case 'g':
            scanf("%lu", &a);
            printf("%lu\n", LGet(l, a));
            break;
        case 'r':
            scanf("%lu", &a);
            LRemove(l, a);
            break;
        case 'R':
            scanf("%lu %lu", &a, &b);
            LRemoveInRange(l, a, b);
            break;
        case 'd':
            LPrint(l);
            break;
        case 'q':
            return 0;
            break;
        case 'h':
            print_help();
            break;
        default:
            printf("unknown commad %c\n", c);
        }
        printf("> ");
    }
    LFree(l);
    return 0;
}
