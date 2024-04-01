#include"list.h"

int main(){
    printf("\nMENU\n");
    printf("a [re] [im] - add element(Example: a 4 3)\n");
    printf("d [re] [im] - delete element(Example: d 4 3)\n");
    printf("s - size\n");
    printf("p - print\n");
    printf("f - delete list and stop\n");
    printf("r [re1] [im1] [re2] [im2] - swap elements(Example: r 4 3 2 1)\n");
    printf("_________________________________\n\n\n");
    Complex a;
    char ch;
    List* l = NewList();
    scanf("%c", &ch);
    while (1){
        if (ch == 'a'){
            scanf("%lg", &a.re);
            scanf("%lg", &a.im);
            Insert(l, a);
        } else if (ch == 'd'){
            scanf("%lg", &a.re);
            scanf("%lg", &a.im);
            Erase(l, a); 
        } else if (ch == 's') {
            printf("%d\n", l->size);
        } else if (ch == 'p') {
            Print(l);
        } else if (ch == 'f') {
            break;
        } else if (ch == 'r') {
            Complex b;
            scanf("%lg", &b.re);
            scanf("%lg", &b.im);
            Complex c;
            scanf("%lg", &c.re);
            scanf("%lg", &c.im);

            SwapElements(l, b, c);  
        }
        if (scanf ("%c", &ch) == EOF) {
            break;
        }
    }

    FreeList(l);
    return 0;

}
