#include <stdio.h>
#include <ctype.h>

int count_nouns() {
    int count = 0;    // Переменная для подсчета количества существительных
    int isWord = 0;   // Флаг, указывающий, что мы считываем слово

    int currentChar = getchar();   // Считываем символы с помощью функции getchar()

    while (currentChar != EOF && currentChar != '\n') {   // Пока не достигнут конец файла или символ новой строки
        if (isalpha(currentChar)) {   // Проверяем, является ли символ буквой
            isWord = 1;   // Устанавливаем флаг, что мы считываем слово
        } else if (isWord) {   // Если прочитали слово
            count++;   // Увеличиваем счетчик на 1
            isWord = 0;   // Сбрасываем флаг слова
        }
        
        currentChar = getchar();   // Считываем следующий символ
    }

    return count;
}

int main() {
    printf("Введите текст на немецком языке:\n");

    int noun_count = count_nouns();
    printf("Количество существительных в тексте: %d\n", noun_count);

    return 0;
}
