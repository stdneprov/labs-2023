#include <stdio.h>
#include <stdlib.h>
#include "tree.h"
#include "stack.h"

void AddOper(Stack* buff, Stack* expr, Elem oper) { /* Добавление оператора в стек */
    if (Empty(buff)) {
        Push(buff, oper);
        return;
    }
    while ((!Empty(buff)) && (Top(buff).priority > oper.priority)) {
        Push(expr, Top(buff));
        Pop(buff);
    }
    Push(buff, oper);
}

void AddUnarMinus(Stack* expr) {
    Elem un;
    un.type = OPER;
    un.val.oper = '-';
    un.priority = -1;
    
    Push(expr, un);
}

void ClosingBracket(Stack* expr, Stack* buff) { /* Обработка скобок */
    if (Empty(buff)) {
        return;
    }
    while ((!Empty(buff)) && (Top(buff).type != OPER || Top(buff).val.oper != '(')) {
        Push(expr, Top(buff));
        Pop(buff);
    }
    Pop(buff);
}

void AddMult(Stack* buff, Stack* expr) { /* Добавление оператора умножения в стек */
    Elem mult;
    mult.type = OPER;
    mult.val.oper = '*';
    mult.priority = 3;
    
    AddOper(buff, expr, mult);
}

void Input(Stack* expr) { /* Перевод выражения в обратную польскую нотацию */
    Stack* buff = InitStack();
    char inp;
    char prevOper;
    Elem elem;
    enum Type prev = OPER;

    while (inp = (char)getchar(), inp != '\n') {

        if (inp >= 'a' && inp <= 'z') { /*Считывание переменной*/
            if (prev == NUM) {
                if (prevOper == '~') {
                    elem.val.num *= -1;
                }
                Push(expr, elem);
                AddMult(buff, expr);
            }
            elem.type = VAR;
            elem.val.var = inp;
            elem.priority = 0;
            Push(expr, elem);
            if (prevOper == '~') {
                AddUnarMinus(expr);
            }
            prev = VAR;
        
        } else if (inp >= '0' && inp <= '9') { /*Считывание числа*/
            if (!(prev == NUM)) {
                if (prev == VAR) {
                    AddMult(buff, expr);
                }
                elem.type = NUM;
                elem.val.num = 0;
                prev = NUM;
                elem.priority = 0;
            }
            int n = inp - '0';
            elem.val.num *= 10;
            elem.val.num += n;
        
        } else if (inp == ' ') {
            continue;
        
        } else { /*Считывание оператора*/
            if (prev == NUM) {
                if (prevOper == '~') {
                    elem.val.num *= -1;
                }
                Push(expr, elem);
                if (inp == '(') {
                    AddMult(buff, expr);
                    prev = OPER;
                }
            } else if (prev == VAR && inp == '(') {
                AddMult(buff, expr);
                prev = OPER;
            }

            elem.type = OPER;
            elem.val.oper = inp;

            switch (inp)
            {
            case '+':
                elem.priority = 1;
                AddOper(buff, expr, elem);
                break;

            case '-':
                if (prev != OPER || prevOper == ')') {
                    elem.priority = 2;
                    AddOper(buff, expr, elem);
                } else {
                    prevOper = '~';
                }
                break;
            
            case '*':
                AddMult(buff, expr);
                break;
            
            case '/':
                elem.priority = 4;
                AddOper(buff, expr, elem);
                break;
            
            case '^':
                elem.priority = 6;
                AddOper(buff, expr, elem);
                break;
            
            case '(':
                elem.priority = 0;
                Push(buff, elem);
                prev = OPER;
                break;

            case ')':
                elem.priority = 0;
                ClosingBracket(expr, buff);
                break;

            default:
                break;
            }
            prev = OPER;

            if (inp != '-') {
                prevOper = inp;
            }
        }
    }
    if (prev == NUM) {
        if (prevOper == '~') {
            elem.val.num *= -1;
        }
        Push(expr, elem);
    }
    while (!Empty(buff)) {
        Push(expr, Top(buff));
        Pop(buff);
    }
    DeleteStack(&buff);
}

void ParseIntoTree(Stack* expr, Node** node) { /* Из стека в дерево */
    if (Empty(expr)) {
        printf("Something wrong\n");
        return;
    }
    Elem elem = Top(expr);
    Pop(expr);
    
    if (elem.type == OPER) {
        if (elem.val.oper != ')') {
            Add(node, elem.val, elem.type, elem.priority);
            ParseIntoTree(expr, &((*node)->rvalue));
        } else {
            ParseIntoTree(expr, node);
        }
        if (elem.val.oper != ')' && elem.val.oper != '(' && elem.priority >= 0) {
            ParseIntoTree(expr, &((*node)->lvalue));
        }
    } else {
        Add(node, elem.val, elem.type, elem.priority);
    }
}

int Pow(int a, int p) { /* Возведение в степень */
    int res = 1;
    int bit = a;
    while (p != 0){
        if (p % 2 > 0){
            res = res * bit;
        }
        bit = bit * bit;
        p /= 2;
    }
    return res;
}

void Eval(Node* node) { /* Задание согласно варианту */
    if (node == NULL) {
        return;
    }
    if (node->type == OPER && node->val.oper == '^') {
        if (node->lvalue->type == NUM && node->rvalue->type == NUM) {
            node->type = NUM;
            node->val.num = Pow(node->lvalue->val.num, node->rvalue->val.num);
            Del(&(node->lvalue));
            Del(&(node->rvalue));
        }
    }
    Eval(node->lvalue);
    Eval(node->rvalue);
}

int main() {
    Stack* expr = InitStack(); 
    
    Input(expr);
    // Проверка содержимого стека
    // while(!Empty(expr)) {
    //     Elem el = Top(expr);
    //     if (el.type == NUM) {
    //         printf("%d\n", el.val.num);
    //     } else {
    //         printf("%c\n", el.val.oper);
    //     }
    //     Pop(expr);
    // }

    putchar('\n');
    Tree tree = InitTree();
    ParseIntoTree(expr, &tree);
    PrintTree(tree, 0);
    putchar('\n');
    PrintExpression(tree);
    printf("\n\n");

    Eval(tree);

    PrintTree(tree, 0);
    putchar('\n');
    PrintExpression(tree);
    putchar('\n');

    Del(&tree);
    DeleteStack(&expr);
}