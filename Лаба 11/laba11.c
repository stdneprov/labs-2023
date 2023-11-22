#include <stdio.h>
#include <string.h>
#include <ctype.h>

int countNouns(const char *text) {
    int count = 0;
    int length = strlen(text);

    for (int i = 0; i < length; i++) {
        // Проверяем, начинается ли слово с заглавной буквы (потенциальное существительное)
        if (isupper(text[i])) {
            // Подсчитываем это слово как существительное
            count++;

            // Пропускаем оставшуюся часть слова
            while (i < length && isalpha(text[i])) {
                i++;
            }
        }
    }

    return count;
}

int main() {
    // Пример текста на немецком языке
    const char *germanText = "Das ist ein Beispieltext für die Programmieraufgabe. "
                             "Es gibt viele Substantive in diesem Text.";

    // Подсчитываем количество существительных и выводим результат
    int nounCount = countNouns(germanText);
    printf("Количество существительных в тексте: %d\n", nounCount);

    return 0;
}