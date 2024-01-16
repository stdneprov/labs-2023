#include <stdio.h>
#include <stdbool.h> //для true/false

int IsSeparator(char c) { //проверяет, является ли данный символ разделителем
    return (c == ' ') || (c == ',') || (c == '\n') || (c == EOF);
}

int IsDigit(char c) { //проверяет, является ли данный символ цифрой
    return c >= '0' && c <= '9';
}

int IsLetterFrom16CC(char c) { //проверяет, есть ли данная буква в алфавите 16сс
    return c >= 'A' && c <= 'F';
}

int LetterTo16CC(char c) { //переводит буквенный символ 16сс-мы в число
    if (c == 'A') {
        return 10;
    }
    if (c == 'B') {
        return 11;
    }
    if (c == 'C') {
        return 12;
    }
    if (c == 'D') {
        return 13;
    }
    if (c == 'E') {
        return 14;
    }
    if (c == 'F') {
        return 15;
    }
    return 0;
}

int NumTo16CCLetter(char c) { //переводит число в буквенный символ 16сс-мы
    if (c == 10) { 
        return 'A';
    }
    if (c == 11) {
        return 'B';
    }
    if (c == 12) {
        return 'C';
    }
    if (c == 13) {
        return 'D';
    }
    if (c == 14) {
        return 'E';
    }
    if (c == 15) {
        return 'F';
    }
    return 0;
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
    int LeadZeros = 0;                  //счетчик лидирующих нулей
    int FixLength = 0;                  //фиксированная длина слова
    int IsFrom16CCFlag = true;          //в данной строке содержится 16-ричное число
    long long buffer = 0;               //буфер содержит 10-тичное представление 16-ричного числа
    int CC16Length = 0;                 //длина числа в 16-ричной сс
    while(1) {
        int ch = getchar();
        if (!IsSeparator(ch)) { 
            FixLength += 1;
            if (ch == '0' && FixLength == 1) { //подсчет лидирующих нулей
                LeadZeros += 1;
                FixLength = 0;
            } else if (IsDigit(ch) && IsFrom16CCFlag == true) { //подсчет допустимых 16-ричных цифр
                buffer = buffer * 16 + ch - '0';
                CC16Length += 1;
            } else if (IsLetterFrom16CC(ch) && IsFrom16CCFlag == true) { //подсчет допустимых 16-ричных букв
                ch = LetterTo16CC(ch);
                CC16Length += 1;
                buffer = buffer * 16 + ch;
            } else {
                IsFrom16CCFlag = false; //ЕСЛИ В СЛОВЕ ОБНАРУЖЕН НЕДОПУСТИМЫЙ СИМВОЛ
                while (LeadZeros != 0) { //сначала выводим лидирующие нули в обычном порядке
                    printf("%c", '0');
                    LeadZeros -= 1;
                }
                if (buffer > 0) { //здесь выводим накопленный буфер в 16сс - представлении
                    while(CC16Length > 0) {
                        int symbol = buffer / Pow(CC16Length - 1) % 16;
                        if (symbol >= 0 && symbol <= 9) {
                            printf("%d", symbol);
                        } else {
                            symbol = NumTo16CCLetter(symbol);
                            printf("%c", symbol);
                        }
                        CC16Length -= 1;
                    }
                }
                printf("%c", ch); //выводим недопустимый символ
            }
        } else if (IsFrom16CCFlag == true) { //ЕСЛИ СЛОВО - ДОПУСТИМОЕ 16-РИЧНОЕ ЧИСЛО
            while(CC16Length > 0) { //сначала выводим число в 16-ричном виде
                int symbol = buffer / Pow(CC16Length - 1) % 16;
                if (symbol >= 0 && symbol <= 9) {
                    printf("%d", symbol);
                } else {
                    symbol = NumTo16CCLetter(symbol);
                    printf("%c", symbol);
                }
                CC16Length -= 1;
            }
            while (LeadZeros != 0) { //дописываем нули (которые теперь стоят в младших разрядах)
                printf("%c", '0');
                LeadZeros -= 1;
            }
            LeadZeros = 0; //обнуление всех показателей
            FixLength = 0;
            IsFrom16CCFlag = true;
            buffer = 0;
            CC16Length = 0;
            printf("\n");
        } else {
            LeadZeros = 0; //обнуление всех показателей
            FixLength = 0;
            IsFrom16CCFlag = true;
            buffer = 0;
            CC16Length = 0;
            printf("\n");
        }
        if (ch == EOF) {
            break;
        }

    }
}
