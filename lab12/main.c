#include <stdio.h>
#include <stdlib.h>


int main() {

    int num;
    
    while (scanf("%d", &num) != EOF) {

        int counter = 0;

        while (num != 0) {

            counter |= (1 << num % 10);
                            
            if (counter >= 1023) {
            
                printf("%d\n", 0);
                break;
            }

            num /= 10;
        }
        
        if (counter < 1023) {

            printf("%d\n", 1);
        }
    }
    
    return 0;
}
