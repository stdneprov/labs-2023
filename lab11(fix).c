#include <stdio.h>
#include <stdbool.h> //для true/false

int IsSeparator(char c) { //проверяет, является ли данный символ разделителем
    return (c == ' ') || (c == ',') || (c == '\n') || (c == EOF) || (c == '\t');
}

int IsDigit(char c) { //проверяет, является ли данный символ цифрой
    return c >= '0' && c <= '9';
}

int IsLetterFrom16CC(char c) { //проверяет, есть ли данная буква в алфавите 16сс
    return c >= 'A' && c <= 'F';
}

int LetterTo10CC(char c) { //перевод буквы 16-ричной сс в 10сс для занесения в буфер
    return (c >= 'A') ? 10 + c - 'A' : c - '0';
}

int Pow(int power) { //возведение числа (16) в степень
    int answer = 1;
    while (power > 0) {
        answer = answer * 16;
        power -= 1;
    }
    return answer;
} 

int main() {
    int leadZeros = 0;                  //счетчик лидирующих нулей
    int fixLength = 0;                  //фиксированная длина слова
    int isFrom16CCFlag = true;          //в данной строке содержится 16-ричное число
    long long buffer = 0;               //буфер содержит 10-тичное представление 16-ричного числа
    int cC16Length = 0;                 //длина числа в 16-ричной сс
    while(1) {
        int ch = getchar();
        if (ch == '-') {
            putchar(ch);
        } else if (!IsSeparator(ch)) { 
            fixLength += 1;
            if (ch == '0' && fixLength == 1) { //подсчет лидирующих нулей
                leadZeros += 1;
                fixLength = 0;
            } else if (IsDigit(ch) && isFrom16CCFlag == true) { //подсчет допустимых 16-ричных цифр
                buffer = buffer * 16 + ch - '0';
                cC16Length += 1;
            } else if (IsLetterFrom16CC(ch) && isFrom16CCFlag == true) { //подсчет допустимых 16-ричных букв
                ch = LetterTo10CC(ch);
                cC16Length += 1;
                buffer = buffer * 16 + ch;
            } else {
                isFrom16CCFlag = false; //ЕСЛИ В СЛОВЕ ОБНАРУЖЕН НЕДОПУСТИМЫЙ СИМВОЛ
                while (leadZeros != 0) { //сначала выводим лидирующие нули в обычном порядке
                    printf("%c", '0');
                    leadZeros -= 1;
                }
                if (buffer > 0) { //здесь выводим накопленный буфер в 16сс - представлении
                    while(cC16Length > 0) {
                        int symbol = buffer / Pow(cC16Length - 1) % 16;
                        if (symbol >= 0 && symbol <= 9) {
                            printf("%d", symbol);
                        } else {
                            symbol += 55; //получаем код буквы (от A до F) по аски
                            printf("%c", symbol); //выводим си мвол по его коду
                        }
                        cC16Length -= 1;
                    }
                }
                printf("%c", ch); //выводим недопустимый символ
            }
        } else if (isFrom16CCFlag == true) { //ЕСЛИ СЛОВО - ДОПУСТИМОЕ 16-РИЧНОЕ ЧИСЛО
            while(cC16Length > 0) { //сначала выводим число в 16-ричном виде
                int symbol = buffer / Pow(cC16Length - 1) % 16;
                if (symbol >= 0 && symbol <= 9) {
                    printf("%d", symbol);
                } else {
                    symbol += 55;
                    printf("%c", symbol);
                }
                cC16Length -= 1;
            }
            while (leadZeros != 0) { //дописываем нули (которые теперь стоят в младших разрядах)
                printf("%c", '0');
                leadZeros -= 1;
            }
            leadZeros = 0; //обнуление всех показателей
            fixLength = 0;
            isFrom16CCFlag = true;
            buffer = 0;
            cC16Length = 0;
            printf("\n");
        } else {
            leadZeros = 0; //обнуление всех показателей
            fixLength = 0;
            isFrom16CCFlag = true;
            buffer = 0;
            cC16Length = 0;
            printf("\n");
        }
        if (ch == EOF) {
            break;
        }

    }
}
