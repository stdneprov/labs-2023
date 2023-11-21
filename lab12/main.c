#include <stdio.h>
#include <stdlib.h>


int main() {

    int num;
    
    while (scanf("%d", &num) != EOF) {

        int counter[10] = {0};
        int sum = 0;

        while (num != 0) {

            if (!counter[num % 10]) {

                counter[num % 10] = 1;
                ++sum;
            }
                            
            if (sum > 9) {
            
                printf("%d\n", 0);
                break;
            }

            num /= 10;
        }
        
        if (sum < 10) {

            printf("%d\n", 1);
        }
    }
    
    return 0;
}