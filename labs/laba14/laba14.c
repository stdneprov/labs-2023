#include <ctype.h>
#include <stdio.h>
#define LEN 1111

int main() {
  char c;
  char s[LEN];
  gets(s);
  int i = 0;
  unsigned long long int prev = 0;
  unsigned long long int word = 0;
  int f = 1;
  while (i < LEN) {
    c = tolower(s[i]);
    if ((c == ' ') || (c == ',') || (c == '\t') || (c == '\n') || c == NULL) {
      if (word != 0) {
        if (word == prev) {
          f = 0;
          printf("1\n");
          break;
        }
        prev = word;
        word = 0;
      }
    } else {
      unsigned long long int ch = 1ull << (c - 'a');
      word = word | ch;
    }
    i++;
  }
  if (f == 1)
    printf("0\n");
  return 0;
}
