#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "item.h"
#include "queue.h"
#include "stack.h"
#include "tree.h"

int IsOperator (int c) {
    return (c == '+') || (c == '-') || (c == '*') || (c == '/') || (c == '^') || (c == '(') || (c == ')') || (c == '\n');
}

int IsNumber(int c) {
    return (c <= '9') && (c >= '0'); 
}

Queue* ReadExpression() {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    queue->head = NULL;
    queue->tail = NULL;
    int c = getchar();
    int numStarted = 0;
    int dot = 0;
    int varStarted = 0;
    double numBuf = 0;
    int maxLenVar = 10;
    int counterChars = 0;
    char *charBuf = (char*)malloc(sizeof(char) * 10);
    while (1) {
        if ((numStarted) && (IsNumber(c)) && (dot == 0)) {
            numBuf = numBuf * 10 + ((double)c - '0');
        } else if ((numStarted) && (IsNumber(c)) && (dot == 1)) {
            numBuf = numBuf + (double)(c - '0') * pow(10, -dot);
            dot++;
        } else if ((numStarted) && (c == '.')) {
            dot = 1;
        } else if ((varStarted) && (c != ' ') && (!(IsOperator(c)))) {
            if (counterChars == maxLenVar) {
                maxLenVar += 10;
                charBuf = realloc(charBuf, sizeof(char) * maxLenVar);
            }
            charBuf[counterChars] = c;
            counterChars++;
        } else if (!(numStarted) && (IsNumber(c))) {
            numStarted = 1;
            numBuf = (double)(c - '0');
        } else if (!(varStarted) && !(IsNumber(c)) && !(IsOperator(c)) && (c != ' ')) {
            varStarted = 1;
            counterChars = 1;
            charBuf[0] = c;
        } else if ((IsOperator(c))) {
            if (numStarted) {
                numStarted = 0;
                dot = 0;
                PushQ(queue, (Item*)malloc(sizeof(Item)));
                queue->tail->value->value.number = numBuf;
                queue->tail->value->type = NUMBER;
            } else if (varStarted) {
                varStarted = 0;
                PushQ(queue, (Item*)malloc(sizeof(Item)));
                queue->tail->value->value.str = (Str*)malloc(sizeof(Str));
                queue->tail->value->value.str->chars = charBuf;
                queue->tail->value->value.str->lenStr = counterChars;
                queue->tail->value->type = VARIABLE;
                charBuf = malloc(sizeof(char) * 10);
                maxLenVar = 10;
            }
            if (IsOperator(c)) {
                PushQ(queue, (Item*)malloc(sizeof(Item)));
                queue->tail->value->value.operator.c = c;
                int p;
                switch (c)
                {
                case '+': p = 3; break;
                case '-': p = 3; break;
                case '*': p = 2; break;
                case '/': p = 2; break;
                case '^': p = 1; break;
                case ')': p = 0; break;
                case '(': p = 4; break;
                default:
                    break;
                }
                queue->tail->value->value.operator.p = p;
                queue->tail->value->type = OPERATOR;
            }
        }

        if (c == '\n') break;
        c = getchar();
    }
    free(charBuf);
    return queue;
}

/*
void PrintExpQ (Queue* exp) {
    int lenVar;
    for (Item *i = PopQ(exp); i != NULL; i = PopQ(exp)) {
        PrintItem(i);
    }
}
*/

Stack* translate (Queue* queue) {
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    Stack* buffer = (Stack*)malloc(sizeof(Stack));
    stack->top = NULL;
    buffer->top = NULL;
    for (Item *i = PopQ(queue); (i->value.operator.c) != '\n'; i = PopQ(queue)) {
        if ((i->type == NUMBER) || (i->type == VARIABLE)) {
            PushS(stack, i);
        } else if (i->type == OPERATOR) {
            Item* topBuf = LookLastS(buffer);
            if (topBuf == NULL) {
                PushS(buffer, i);
            } else if ((i->value.operator.c != '(') && (i->value.operator.c != ')')) {
                if (topBuf->value.operator.p <= i->value.operator.p) {
                    for (Item *s = LookLastS(buffer); ((s != NULL) && (s->value.operator.c != '(')); s = LookLastS(buffer)) {
                        if (s->value.operator.p > i->value.operator.p) break;
                        if (s->value.operator.c != '(') {
                            PopS(buffer);
                            PushS(stack, s);
                        }
                    }
                    PushS(buffer, i);
                } else {
                    PushS(buffer, i);
                }
            } else if (i->value.operator.c == '(') {
                PushS(buffer, i);
            } else if (i->value.operator.c == ')') {
                for (Item *s = LookLastS(buffer); ((s != NULL) && (s->value.operator.c != '(')); s = LookLastS(buffer)) {
                    if (s->value.operator.c != '(') {
                        PopS(buffer);
                        PushS(stack, s);
                    }
                }
                PopS(buffer);
            }
        }
    } 
    for (Item *s = LookLastS(buffer); (s != NULL); s = LookLastS(buffer)) {
        PopS(buffer);
        PushS(stack, s);
    }
    return stack;
}

/*
void PrintExpS (Stack* exp) {

    for (Item *i = PopS(exp); i != NULL; i = PopS(exp)) {
        PrintItem(i);
    }
}
*/

void func (Node* tree) {
    if (tree == NULL) {
        return;
    }
    func(tree->l);
    func(tree->r);
    if ((tree->value->type == OPERATOR) &&
    (tree->value->value.operator.c == '*') &&
    (tree->l->value->type == OPERATOR) && (tree->r->value->type == OPERATOR) &&
    (tree->l->value->value.operator.c == '^') && (tree->r->value->value.operator.c == '^') &&
    (EqualTrees(tree->l->l, tree->r->l))) {
        tree->value->value.operator.c = '^';
        tree->r->value->value.operator.c = '+';
        TreeDestroy(tree->r->l);
        tree->r->l = tree->l->r;
        Node* toDel = tree->l;
        tree->l = tree->l->l;
        DelItem(toDel->value);
        free(toDel);
    }
}

void PrintExp (Node* tree) {
    if (tree->value->type == OPERATOR) {
        printf("(");
        PrintExp(tree->l);
        PrintItem(tree->value);
        PrintExp(tree->r);
        printf(")");
    } else {
        PrintItem(tree->value);
    }
}

int main() {
    while(1) {
        Queue* exp = ReadExpression();
        Stack* expp = translate(exp);
        free(exp);
        Node* tree = NULL;
        for (Item* i = PopS(expp); i != NULL; i = PopS(expp)) {
            TreePush(&tree, i);
        }
        free(expp);
        func(tree);
        PrintExp(tree);
        printf("\n");
        TreeDestroy(tree);
    }
    return 0;
}