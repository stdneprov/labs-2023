// поменять местами вторую и предпоследнюю
// учесть разрядность int на машине (4 или 2 байта)
// тесты

#include "lab12_var18.h"

// функция считает количество цифр в числе
int amount_of_digits(int n) {
  int digits = 0;

  do {
    n /= 10;
    digits++;
  } while (n != 0);

  return digits;
}

// меняет местами два числа - предпоследнее и второе с начала
int change_2nd_and_prelast(int n) {
  int digits = amount_of_digits(n);
  if (digits < 2) {
    return n;
  }

  char s[digits + 1]; // создаем стоку, в которую запишем число n
  sprintf(s, "%d", n); // переводим число из типа int в строку

  char left = s[1]; // второй символ с начала строки
  char right = s[digits - 2]; // предпоследнй символ строки
  s[1] = right;
  s[digits - 2] = left;

  n = atoi(s); // обратно переводим строку в число

  return n;
}