#include "base.h"

#include "stack.h"
#include "tree.h"
char buffChar = 0;
char prevOperarion = 1;

Token GetToken() {
    Token token;
    token.sign = 1;
    if (buffChar != 0) {
        token.val.letter = buffChar;
        if (GetPriority(buffChar) != -1) {
            token.type = OPERATOR;
        } else {
            token.type = VAR;
        }
        buffChar = 0;
        if (prevOperarion && token.val.letter == '-') {
            prevOperarion = 0;
            token = GetToken();
            token.sign = -1;
            return token;
        }
        prevOperarion = token.type == OPERATOR;
        return token;
    }
    char inp = getchar();
    if (GetPriority(inp) != -1) {
        if (prevOperarion && inp == '-') {
            prevOperarion = 0;
            token = GetToken();
            token.sign = -1;
            return token;
        }
        token.sign = 1;
        token.type = OPERATOR;
        token.val.letter = inp;
        prevOperarion = token.type == OPERATOR;
        return token;
    } else if (IsDigit(inp)) {
        int value = inp - '0';
        while (IsDigit(inp = getchar())) {
            value = value * 10 + (inp - '0');
        }
        buffChar = inp;
        token.type = NUM;
        token.val.num = value;
        prevOperarion = token.type == OPERATOR;
        return token;
    } else {
        token.type = VAR;
        token.val.letter = inp;
        prevOperarion = token.type == OPERATOR;
        return token;
    }
}

int GetPriority(char operator) {
    switch (operator) {
        case '+':
            return 1;
        case '-':
            return 2;
        case '*':
            return 3;
        case '/':
            return 4;
        case '^':
            return 5;
        case '(':
            return 0;
        case ')':
            return 0;
        default:
            return -1;
    }
}

int IsDigit(char c) { return c >= '0' && c <= '9'; }
int IsLetter(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

int gcd(int a, int b) {
    if (a == 0) return b;
    return gcd(b % a, a);
}