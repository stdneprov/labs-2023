#include <stdio.h>      /* Standard Library of Input and Output */
#include <complex.h>    /* Standard Library of Complex Numbers */
#include "slovar.h"
#include <string.h>
#define I _Complex_I

void Hello() {
    printf("Это меню управления программой\n");
    printf("Если хочешь добавить значение - введи push и в следующей строке 3 значения: целую часть, мнимую часть, значение\n");
    printf("Если хочешь отсортировать - введи sort\n");
    printf("Если хочешь посмотреть таблицу - введи print\n");
    printf("Если хочешь узнать размер - введи size\n");
    printf("Если хочешь удалить значение - введи pop и в следующей строке ключ\n");
    printf("Если хочешь выйти - введи exit или ctrl+D\n");
    printf("В случае неверной команды ничего не произойдет\n");
}


void Menu() {
    Hello();
    Table tb = TableInit();

    char inputUser[10] = "";


    while(!feof(stdin)) {
        char inputUser[10] = "";
        fgets(inputUser, sizeof(char) * 10, stdin);
        fflush(stdin);
        if (strcmp(inputUser, "print\n") == 0) {
            if (TableIsEmpty(&tb)) {
                printf("словарь не задан\n");
            } else {
                //printf("Бинарное дерево\n");
                TablePrint(&tb);
                printf("\n");
            }

        } else if (strcmp(inputUser, "sort\n") == 0){
            for (int i = 0; i < TableSize(&tb); i++) {
                Sort(&tb);
            }
            continue;
        } else if (strcmp(inputUser, "push\n") == 0) {
            double a, b;
            int c;
            scanf("%lf %lf %d", &a, &b, &c);
            TablePush(&tb, a, b, c);
            continue;
        } else if (strcmp(inputUser, "size\n") == 0) {
            printf("%d\n", TableSize(&tb));

            continue;
        } else if ((strcmp(inputUser, "exit\n") == 0)) {
            break;
        }
    }

}



int main() {

    // double complex z1 = 1.0 + 3.0 * I;
    // double complex z2;//z2 = 1.0 - 4.0 * I;
    // double a, b;
    // scanf("%lf %lf", &a, &b);
    // z2 = a + b * I;

    // printf("Working with complex numbers:\n\v");

    // printf("Starting values: Z1 = %.2f + %.2fi\tZ2 = %.2f %+.2fi\n", creal(z1), cimag(z1), creal(z2), cimag(z2));

    // double complex sum = z1 + z2;
    // printf("The sum: Z1 + Z2 = %.2f %+.2fi\n", creal(sum), cimag(sum));

    // double complex difference = z1 - z2;
    // printf("The difference: Z1 - Z2 = %.2f %+.2fi\n", creal(difference), cimag(difference));

    // double complex product = z1 * z2;
    // printf("The product: Z1 x Z2 = %.2f %+.2fi\n", creal(product), cimag(product));

    // double complex quotient = z1 / z2;
    // printf("The quotient: Z1 / Z2 = %.2f %+.2fi\n", creal(quotient), cimag(quotient));

    // double complex conjugate = conj(z1);
    // printf("The conjugate of Z1 = %.2f %+.2fi\n", creal(conjugate), cimag(conjugate));
    Menu();
    return 0;
}