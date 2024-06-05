#include <stdio.h>      /* Standard Library of Input and Output */
#include "table.h"
#include <string.h>

void Hello() {
    printf("Меню управления программой\n");
    printf("Добавить значение - введите push и в следующей строке 2 значения: key and value\n");
    printf("Отсортировать - введите sort\n");
    printf("Посмотреть таблицу - введите print\n");
    printf("Узнать размер - введите size\n");
    printf("Найти значение - введите find и в следующей строке key\n");
    printf("Выйти - введите exit или ctrl+C\n");
    printf("В случае неверной команды ничего не произойдет\n");
}

void YourStep(Table *tb) {
    TableSort(&tb);
}

void Find(Table *table, double a) {
    while(table != NULL) {
        if (table->key == a) {
            printf("%d\n", table->val);
            return;
        }
        table = table->next;
    }
    printf("NE Naideno");
    return;
}

void Menu() {
    Hello();
    Table tb = TableInit();

    char inputUser[10] = "";

    while(!feof(stdin)) {
        fgets(inputUser, sizeof(char) * 10, stdin);
           char inputUser[10] = "";     fflush(stdin);
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
                YourStep(&tb);

            }
            continue;
        } else if (strcmp(inputUser, "push\n") == 0) {
            double a;
            int c;
            scanf("%lf %d", &a, &c);
            TablePush(&tb, a, c);
            continue;
        } else if (strcmp(inputUser, "size\n") == 0) {
            printf("%d\n", TableSize(&tb));

            continue;
        } else if ((strcmp(inputUser, "exit\n") == 0)) {
            break;
        } else if (strcmp(inputUser, "find\n") == 0) {
            double a;
            printf("vvedi:\n");
            scanf("%lf", &a);
            Find(&tb, a);

            continue;
        }
    }

}


int main() {
    Menu();
    return 0;
}
