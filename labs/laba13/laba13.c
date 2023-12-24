#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

int main()
{
    int word_count, max_word_len;
    printf("Enter count of words: ");
    scanf("%d", &word_count);
    getchar();
    printf("Enter maximum length of word: ");
    scanf("%d", &max_word_len);
    getchar();
    char **words = (char **)malloc(word_count * sizeof(char *));
    if (!words)
    {
        printf("Failed to allocate memory!");
        return -1;
    }
    
    for (int i = 0; i < word_count; ++i)
    {
        words[i] = malloc(max_word_len);
    }
    
    printf("Enter words:\n");
    int word_ind = 0;
    int letter_ind = 0;
    char c;
    while ((c = getchar()) != EOF)
    {
        if (c == ' ' || c == '\t' || c == '\n' || c == ',')
        {
            words[word_ind][letter_ind] = 0;
            word_ind += 1;
            letter_ind = 0;
            continue;
        }
        
        words[word_ind][letter_ind] = c;
        ++letter_ind;
    }
    
    for (int i = 0; i < word_count - 1; ++i)
    {
        unsigned int word1 = 0;
        unsigned int word2 = 0;
        for (int j = 0; words[i][j] != 0; ++j)
        {
            unsigned int tmp_set = 1u << (words[i][j] - 'a');
            word1 |= tmp_set;
        }
        
        for (int j = 0; words[i + 1][j] != 0; ++j)
        {
            unsigned int tmp_set = 1u << (words[i + 1][j] - 'a');
            word2 |= tmp_set;
        }
        
        if (word1 == word2)
        {
            printf("There are such words!\n");
            return 0;
        }
        printf("\n");
    }
    
    printf("There are no such words!");
    return 0;
}