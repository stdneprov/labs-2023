#include <stdio.h>
#include <stdbool.h>
int IsSeparator(char c) {
    return (c == ' ') || (c == ',') || (c == '\n') || (c == EOF);
}

int main(){
    int WordCounter = 0;
    bool CommentStarted = 0;
    bool WordStarted = 0;
    int PredSymbol = 0;

    while (1) {
        int c = getchar();
        if (!IsSeparator(c)) {
            if (c == '{' || (c == '*' && PredSymbol == '(')){
                CommentStarted = 1;
                WordStarted = 0;
            }
            else if (c == '}' || c == ')' && PredSymbol == '*'){
                CommentStarted = 0;
                if (WordStarted){
                    WordStarted = 0;
                    WordCounter += 1;
                }
            }
            else{
                if (c != '*'){
                    WordStarted = 1;
                }

            }

        } else {
            if (WordStarted && CommentStarted){
                WordCounter += 1;
                WordStarted = 0;
            }
            WordStarted = 0;
        }
        PredSymbol = c;
        if (c == EOF) {
            break;
        }
    }

    printf("%d", WordCounter);

}
