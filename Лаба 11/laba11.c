#include <stdio.h>
#include <ctype.h>

int count_nouns() {
    int count = 0;    
    int isWord = 0;   
    int currentChar = getchar();   
    while (currentChar != EOF && currentChar != '\n') {  
        if (isalpha(currentChar)) {   
            isWord = 1;  
        } else if (isWord) {  
            count++;  
            isWord = 0;   
        }
        currentChar = getchar();   
    }
    return count;
}

int main() {
    printf("Введите текст на немецком языке:\n");
    int noun_count = count_nouns();
    printf("Количество существительных в тексте: %d\n", noun_count);
    return 0;
}
