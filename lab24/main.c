#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef enum ValueType {
    ValueTypeOp,
    ValueTypeVal,
    ValueTypeName,
} ValueType;

typedef union ValueValue {
    char op;
    float val;
    char name[32];
} ValueValue;

typedef struct Value {
    ValueType t;
    ValueValue v;
} Value;

void PrintValue(Value *v) {
    if (v->t == ValueTypeOp) {
        printf("%c", v->v.op);
    } else if (v->t == ValueTypeVal) {
        printf("%f", v->v.val);
    } else {
        printf("%s", v->v.name);
    }
}

typedef struct List {
    int index;
    int size;
    Value *v;
} List;

bool ListEmpty(List *l) {
    return l->index <= 0;
}

void ListPush(List *l, Value v) {
    if (l->size == 0) {
        l->v = (Value *)malloc(1 * sizeof(Value));
        if (l->v == NULL) {
            printf("ERROR: buy more ram\n");
            exit(1);
        }
        l->size = 1;
    } else if (l->index >= l->size) {
        Value *v = (Value *)realloc(l->v, l->size * sizeof(Value) * 2);
        if (v == NULL) {
            printf("ERROR: buy more ram\n");
            exit(1);
        }
        l->v = v;
        l->size = l->size * 2;
    }
    l->v[l->index++] = v;
}

Value ListPop(List *l) {
    if (ListEmpty(l)) {
        printf("ERROR: out of bounds");
        exit(1);
    }
    return l->v[--l->index];
}

Value *ListLast(List *l) {
    if (ListEmpty(l)) {
        return NULL;
    }
    return &l->v[l->index - 1];
}

Value *ListGet(List *s, unsigned int i) {
    return &s->v[i];
}

int ListLen(List *s) {
    return s->index;
}

bool IsOperand(char c) {
    char ops[] = "+-/*()^";
    for (int i = 0; i < (int)(sizeof(ops) / sizeof(ops[0])); i++) {
        if (ops[i] == c) {
            return true;
        }
    }
    return false;
}

void PushValue(List *s, Value *v, char str[256], int *s_i) {
    char *err;
    float f = strtof(str, &err);
    if (err != str) {
        v->t = ValueTypeVal;
        v->v.val = f;
        ListPush(s, *v);
    }
    if (*err) {
        strcpy(v->v.name, err);
        v->t = ValueTypeName;
        ListPush(s, *v);
    }

    for (int i = 0; i < 256; i++)
        str[i] = 0;
    *s_i = -1;
}

int OperandPriority(Value v) {
    if (v.t != ValueTypeOp) {
        printf("ERROR: not an operand\n");
        exit(1);
    }
    char op = v.v.op;
    if (op == '(')
        return 0;
    if (op == '+' || op == '-')
        return 1;
    if (op == '*' || op == '/')
        return 2;
    if (op == '^')
        return 3;
    printf("ERROR: unknown operand: %c\n", op);
    exit(1);
}

List ConvertToReversePolish(char *str) {
    List res = {0};
    List stack = {0};
    Value cur = {0};
    Value last = {0};
    Value p = {0};
    char strbuf[256] = {0};
    int i_strbuf = -1;
    char prev = ' ';
    while (*str) {
        if (IsOperand(*str) || *str == ' ') {
            if (prev != ' ' && !IsOperand(prev) && strbuf[0]) {
                PushValue(&res, &cur, strbuf, &i_strbuf);
                p = cur;
            }
            if (*str == ' ') {
                while (*(++str) == ' ')
                    continue;
                prev = ' ';
                continue;
            } else {
                cur.t = ValueTypeOp;
                cur.v.op = *str;
                if (cur.v.op == ')') {
                    while (!ListEmpty(&stack)) {
                        last = *ListLast(&stack);
                        ListPop(&stack);
                        if (last.v.op == '(') {
                            break;
                        }
                        ListPush(&res, last);
                    }
                } else if (cur.v.op == '(') {
                    ListPush(&stack, cur);
                    p = cur;
                } else {
                    if (cur.v.op == '-' && p.t == ValueTypeOp) {
                        Value q = {0};
                        q.t = ValueTypeVal;
                        q.v.val = -1.0;
                        ListPush(&res, q);
                        q.t = ValueTypeOp;
                        q.v.op = '*';
                        ListPush(&stack, q);
                    } else {
                        while (!ListEmpty(&stack)) {
                            last = *ListLast(&stack);
                            if (OperandPriority(cur) <= OperandPriority(last)) {
                                ListPop(&stack);
                                ListPush(&res, last);
                                continue;
                            }
                            break;
                        }
                        ListPush(&stack, cur);
                        p = cur;
                    }
                }
            }
        } else {
            strbuf[++i_strbuf] = *str;
        }
        prev = *str;
        str++;
    }
    PushValue(&res, &cur, strbuf, &i_strbuf);
    while (!ListEmpty(&stack)) {
        last = *ListLast(&stack);
        ListPush(&res, last);
        ListPop(&stack);
    }
    free(stack.v);

    return res;
}

typedef struct Tree {
    Value val;
    struct Tree *l;
    struct Tree *r;
} Tree;

Tree GenerateTreeFromReversePolish(List *l) {
    Tree t = {0};
    t.val = *ListLast(l);
    ListPop(l);
    if (t.val.t == ValueTypeOp) {
        t.l = malloc(sizeof(Tree));
        t.r = malloc(sizeof(Tree));
        *t.r = GenerateTreeFromReversePolish(l);
        *t.l = GenerateTreeFromReversePolish(l);
    }
    return t;
}

void PrintTree(Tree *t, int depth) {
    for (int i = 0; i < depth * 4; i++) {
        printf(" ");
    }
    PrintValue(&t->val);
    printf("\n");
    if (t->l)
        PrintTree(t->l, depth + 1);
    if (t->r)
        PrintTree(t->r, depth + 1);
}

void PrintTreeAsExpressionR(Tree *t) {
    if (t->l && t->r) {
        printf("(");
        if (t->l)
            PrintTreeAsExpressionR(t->l);
        PrintValue(&t->val);
        if (t->r)
            PrintTreeAsExpressionR(t->r);
        printf(")");
    } else {
        PrintValue(&t->val);
    }
}
void PrintTreeAsExpression(Tree *t) {
    PrintTreeAsExpressionR(t);
    printf("\n");
}

int main(void) {
    // упрастить выполнив деление
    char *str = "a * -(b + c * d) / 2";
    printf("%s\n\n", str);
    List l = ConvertToReversePolish(str);
    for (int i = 0; i < l.index; i++) {
        printf("%d: ", i);
        PrintValue(&l.v[i]);
        printf("\n");
    }
    printf("\n");
    Tree t = GenerateTreeFromReversePolish(&l);
    PrintTree(&t, 0);
    printf("\n");
    PrintTreeAsExpression(&t);

    return 0;
}
