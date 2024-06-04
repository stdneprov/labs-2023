#include <stdlib.h>
#include <stdio.h>
#include "stack.h"
#include "tree.h"
#include <stdbool.h>

void ForNUM(Node **tree, Stack *num, Stack *var, int k) {
    (*tree)->left = NULL;
    (*tree)->right = NULL;
    (*tree)->type = SYMB;
    Stack m = StackInit();
    StackPush(&m, '*', SYMB);
    (*tree)->key = StackPop(&m);
    if (StackIsEmpty(var)) {
        if (StackSize(num) == 1) {
            Stack m = StackInit();
            StackPush(&m, '^', SYMB);
            (*tree)->key = StackPop(&m);
            (*tree)->left = (Node *)malloc(sizeof(Node));
            (*tree)->left->left = NULL;
            (*tree)->left->right = NULL;
            (*tree)->right = (Node *)malloc(sizeof(Node));
            (*tree)->right->left = NULL;
            (*tree)->right->right = NULL;
            (*tree)->left->type = NUM;
            (*tree)->right->type = NUM;
            (*tree)->left->key.num = k;
            (*tree)->right->key = StackPop(num);
        } else {
            (*tree)->left = (Node *)malloc(sizeof(Node));
            (*tree)->left->left = NULL;
            (*tree)->left->right = NULL;
            (*tree)->left->left = (Node *)malloc(sizeof(Node));
            (*tree)->left->left->left = NULL;
            (*tree)->left->left->right = NULL;
            (*tree)->left->right = (Node *)malloc(sizeof(Node));
            (*tree)->left->right->left = NULL;
            (*tree)->left->right->right = NULL;
            (*tree)->left->left = (Node *)malloc(sizeof(Node));
            (*tree)->left->left->left = NULL;
            (*tree)->left->left->right = NULL;
            (*tree)->right = (Node *)malloc(sizeof(Node));
            (*tree)->left->type = SYMB;
            Stack m = StackInit();
            StackPush(&m, '^', SYMB);
            (*tree)->left->key = StackPop(&m);
            (*tree)->left->left->type = NUM;
            (*tree)->left->right->type = NUM;
            (*tree)->left->left->key.num = k;
            (*tree)->left->right->key = StackPop(num);
            ForNUM(&(*tree)->right, num, var, k);
        }
    } else if (StackIsEmpty(num)) {
        if (StackSize(var) == 1) {
            Stack m = StackInit();
            StackPush(&m, '^', SYMB);
            (*tree)->key = StackPop(&m);
            (*tree)->left = (Node *)malloc(sizeof(Node));
            (*tree)->left->left = NULL;
            (*tree)->left->right = NULL;
            (*tree)->right = (Node *)malloc(sizeof(Node));
            (*tree)->right->left = NULL;
            (*tree)->right->right = NULL;
            (*tree)->left->type = NUM;
            (*tree)->right->type = VAR;
            (*tree)->left->key.num = k;
            (*tree)->right->key = StackPop(var);
        } else {
            (*tree)->left = (Node *)malloc(sizeof(Node));
            (*tree)->left->left = NULL;
            (*tree)->left->right = NULL;
            (*tree)->left->left = (Node *)malloc(sizeof(Node));
            (*tree)->left->left->left = NULL;
            (*tree)->left->left->right = NULL;
            (*tree)->left->right = (Node *)malloc(sizeof(Node));
            (*tree)->left->right->left = NULL;
            (*tree)->left->right->right = NULL;
            (*tree)->left->left = (Node *)malloc(sizeof(Node));
            (*tree)->left->left->left = NULL;
            (*tree)->left->left->right = NULL;
            (*tree)->right = (Node *)malloc(sizeof(Node));
            (*tree)->left->type = SYMB;
            Stack m = StackInit();
            StackPush(&m, '^', SYMB);
            (*tree)->left->key = StackPop(&m);
            (*tree)->left->left->type = NUM;
            (*tree)->left->right->type = VAR;
            (*tree)->left->left->key.num = k;
            (*tree)->left->right->key = StackPop(var);
            ForNUM(&(*tree)->right, num, var, k);
        }
    } else {
        (*tree)->left = (Node *)malloc(sizeof(Node));
        (*tree)->left->left = NULL;
        (*tree)->left->right = NULL;
        (*tree)->left->left = (Node *)malloc(sizeof(Node));
        (*tree)->left->left->left = NULL;
        (*tree)->left->left->right = NULL;
        (*tree)->left->right = (Node *)malloc(sizeof(Node));
        (*tree)->left->right->left = NULL;
        (*tree)->left->right->right = NULL;
        (*tree)->left->left = (Node *)malloc(sizeof(Node));
        (*tree)->left->left->left = NULL;
        (*tree)->left->left->right = NULL;
        (*tree)->right = (Node *)malloc(sizeof(Node));
        (*tree)->left->type = SYMB;
        Stack m = StackInit();
        StackPush(&m, '^', SYMB);
        (*tree)->left->key = StackPop(&m);
        (*tree)->left->left->type = NUM;
        (*tree)->left->right->type = NUM;
        (*tree)->left->left->key.num = k;
        (*tree)->left->right->key = StackPop(num);
        ForNUM(&(*tree)->right, num, var, k);
    }

}

void ForVAR(Node **tree, Stack *num, Stack *var, char k) {
    (*tree)->left = NULL;
    (*tree)->right = NULL;
    (*tree)->type = SYMB;
    Stack m = StackInit();
    StackPush(&m, '*', SYMB);
    (*tree)->key = StackPop(&m);
    if (StackIsEmpty(var)) {
        if (StackSize(num) == 1) {
            Stack m = StackInit();
            StackPush(&m, '^', SYMB);
            (*tree)->key = StackPop(&m);
            (*tree)->left = (Node *)malloc(sizeof(Node));
            (*tree)->left->left = NULL;
            (*tree)->left->right = NULL;
            (*tree)->right = (Node *)malloc(sizeof(Node));
            (*tree)->right->left = NULL;
            (*tree)->right->right = NULL;
            (*tree)->left->type = VAR;
            (*tree)->right->type = NUM;
            StackPush(&m, k, VAR);
            (*tree)->left->key = StackPop(&m);
            (*tree)->right->key = StackPop(num);
        } else {
            (*tree)->left = (Node *)malloc(sizeof(Node));
            (*tree)->left->left = NULL;
            (*tree)->left->right = NULL;
            (*tree)->left->left = (Node *)malloc(sizeof(Node));
            (*tree)->left->left->left = NULL;
            (*tree)->left->left->right = NULL;
            (*tree)->left->right = (Node *)malloc(sizeof(Node));
            (*tree)->left->right->left = NULL;
            (*tree)->left->right->right = NULL;
            (*tree)->left->left = (Node *)malloc(sizeof(Node));
            (*tree)->left->left->left = NULL;
            (*tree)->left->left->right = NULL;
            (*tree)->right = (Node *)malloc(sizeof(Node));
            (*tree)->left->type = SYMB;
            Stack m = StackInit();
            StackPush(&m, '^', SYMB);
            (*tree)->left->key = StackPop(&m);
            (*tree)->left->left->type = VAR;
            (*tree)->left->right->type = NUM;
            StackPush(&m, k, VAR);
            (*tree)->left->left->key = StackPop(&m);
            (*tree)->left->right->key = StackPop(num);
            ForVAR(&(*tree)->right, num, var, k);
        }
    } else if (StackIsEmpty(num)) {
        if (StackSize(var) == 1) {
            Stack m = StackInit();
            StackPush(&m, '^', SYMB);
            (*tree)->key = StackPop(&m);
            (*tree)->left = (Node *)malloc(sizeof(Node));
            (*tree)->left->left = NULL;
            (*tree)->left->right = NULL;
            (*tree)->right = (Node *)malloc(sizeof(Node));
            (*tree)->right->left = NULL;
            (*tree)->right->right = NULL;
            (*tree)->left->type = VAR;
            (*tree)->right->type = VAR;
            StackPush(&m, k, VAR);
            (*tree)->left->key = StackPop(&m);
            (*tree)->right->key = StackPop(var);
        } else {
            (*tree)->left = (Node *)malloc(sizeof(Node));
            (*tree)->left->left = NULL;
            (*tree)->left->right = NULL;
            (*tree)->left->left = (Node *)malloc(sizeof(Node));
            (*tree)->left->left->left = NULL;
            (*tree)->left->left->right = NULL;
            (*tree)->left->right = (Node *)malloc(sizeof(Node));
            (*tree)->left->right->left = NULL;
            (*tree)->left->right->right = NULL;
            (*tree)->left->left = (Node *)malloc(sizeof(Node));
            (*tree)->left->left->left = NULL;
            (*tree)->left->left->right = NULL;
            (*tree)->right = (Node *)malloc(sizeof(Node));
            (*tree)->left->type = SYMB;
            Stack m = StackInit();
            StackPush(&m, '^', SYMB);
            (*tree)->left->key = StackPop(&m);
            (*tree)->left->left->type = VAR;
            (*tree)->left->right->type = VAR;
            StackPush(&m, k, VAR);
            (*tree)->left->left->key = StackPop(&m);
            (*tree)->left->right->key = StackPop(var);
            ForVAR(&(*tree)->right, num, var, k);
        }
    } else {
        (*tree)->left = (Node *)malloc(sizeof(Node));
        (*tree)->left->left = NULL;
        (*tree)->left->right = NULL;
        (*tree)->left->left = (Node *)malloc(sizeof(Node));
        (*tree)->left->left->left = NULL;
        (*tree)->left->left->right = NULL;
        (*tree)->left->right = (Node *)malloc(sizeof(Node));
        (*tree)->left->right->left = NULL;
        (*tree)->left->right->right = NULL;
        (*tree)->left->left = (Node *)malloc(sizeof(Node));
        (*tree)->left->left->left = NULL;
        (*tree)->left->left->right = NULL;
        (*tree)->right = (Node *)malloc(sizeof(Node));
        (*tree)->left->type = SYMB;
        Stack m = StackInit();
        StackPush(&m, '^', SYMB);
        (*tree)->left->key = StackPop(&m);
        (*tree)->left->left->type = VAR;
        (*tree)->left->right->type = NUM;
        StackPush(&m, k, VAR);
        (*tree)->left->left->key = StackPop(&m);
        (*tree)->left->right->key = StackPop(num);
        ForVAR(&(*tree)->right, num, var, k);
    }

}

void ForSYMB(Node **tree, Stack *num, Stack *var, Node *k) {
    (*tree)->left = NULL;
    (*tree)->right = NULL;
    (*tree)->type = SYMB;
    Stack m = StackInit();
    StackPush(&m, '*', SYMB);
    (*tree)->key = StackPop(&m);
    if (StackIsEmpty(var)) {
        if (StackSize(num) == 1) {
            Stack m = StackInit();
            StackPush(&m, '^', SYMB);
            (*tree)->key = StackPop(&m);
            (*tree)->left = (Node *)malloc(sizeof(Node));
            (*tree)->left->left = NULL;
            (*tree)->left->right = NULL;
            (*tree)->right = (Node *)malloc(sizeof(Node));
            (*tree)->right->left = NULL;
            (*tree)->right->right = NULL;
            (*tree)->right->type = NUM;
            (*tree)->left = k;
            (*tree)->right->key = StackPop(num);
        } else {
            (*tree)->left = (Node *)malloc(sizeof(Node));
            (*tree)->left->left = NULL;
            (*tree)->left->right = NULL;
            (*tree)->left->left = (Node *)malloc(sizeof(Node));
            (*tree)->left->left->left = NULL;
            (*tree)->left->left->right = NULL;
            (*tree)->left->right = (Node *)malloc(sizeof(Node));
            (*tree)->left->right->left = NULL;
            (*tree)->left->right->right = NULL;
            (*tree)->left->left = (Node *)malloc(sizeof(Node));
            (*tree)->left->left->left = NULL;
            (*tree)->left->left->right = NULL;
            (*tree)->right = (Node *)malloc(sizeof(Node));
            (*tree)->left->type = SYMB;
            Stack m = StackInit();
            StackPush(&m, '^', SYMB);
            (*tree)->left->key = StackPop(&m);
            (*tree)->left->right->type = NUM;
            (*tree)->left->left = k;
            (*tree)->left->right->key = StackPop(num);
            ForSYMB(&(*tree)->right, num, var, k);
        }
    } else if (StackIsEmpty(num)) {
        if (StackSize(var) == 1) {
            Stack m = StackInit();
            StackPush(&m, '^', SYMB);
            (*tree)->key = StackPop(&m);
            (*tree)->left = (Node *)malloc(sizeof(Node));
            (*tree)->left->left = NULL;
            (*tree)->left->right = NULL;
            (*tree)->right = (Node *)malloc(sizeof(Node));
            (*tree)->right->left = NULL;
            (*tree)->right->right = NULL;
            (*tree)->right->type = VAR;
            (*tree)->left = k;
            (*tree)->right->key = StackPop(var);
        } else {
            (*tree)->left = (Node *)malloc(sizeof(Node));
            (*tree)->left->left = NULL;
            (*tree)->left->right = NULL;
            (*tree)->left->left = (Node *)malloc(sizeof(Node));
            (*tree)->left->left->left = NULL;
            (*tree)->left->left->right = NULL;
            (*tree)->left->right = (Node *)malloc(sizeof(Node));
            (*tree)->left->right->left = NULL;
            (*tree)->left->right->right = NULL;
            (*tree)->left->left = (Node *)malloc(sizeof(Node));
            (*tree)->left->left->left = NULL;
            (*tree)->left->left->right = NULL;
            (*tree)->right = (Node *)malloc(sizeof(Node));
            (*tree)->left->type = SYMB;
            Stack m = StackInit();
            StackPush(&m, '^', SYMB);
            (*tree)->left->key = StackPop(&m);
            (*tree)->left->right->type = VAR;
            (*tree)->left->left = k;
            (*tree)->left->right->key = StackPop(var);
            ForSYMB(&(*tree)->right, num, var, k);
        }
    } else {
        (*tree)->left = (Node *)malloc(sizeof(Node));
        (*tree)->left->left = NULL;
        (*tree)->left->right = NULL;
        (*tree)->left->left = (Node *)malloc(sizeof(Node));
        (*tree)->left->left->left = NULL;
        (*tree)->left->left->right = NULL;
        (*tree)->left->right = (Node *)malloc(sizeof(Node));
        (*tree)->left->right->left = NULL;
        (*tree)->left->right->right = NULL;
        (*tree)->left->left = (Node *)malloc(sizeof(Node));
        (*tree)->left->left->left = NULL;
        (*tree)->left->left->right = NULL;
        (*tree)->right = (Node *)malloc(sizeof(Node));
        (*tree)->left->type = SYMB;
        Stack m = StackInit();
        StackPush(&m, '^', SYMB);
        (*tree)->left->key = StackPop(&m);
        (*tree)->left->right->type = NUM;
        (*tree)->left->left = k;
        (*tree)->left->right->key = StackPop(num);
        ForSYMB(&(*tree)->right, num, var, k);
    }

}

void PrintResult(Node* tree) {
    if (tree->left == NULL && tree->right == NULL) {
        if (tree->type == SYMB) {
            printf("%c", *tree->key.symb);
        } else if (tree->type == VAR) {
            printf("%c", *tree->key.symb);
        } else {
            printf("%d", tree->key.num);
        }
        return;
    } 
    if (tree->left != NULL) {
        printf("(");
        PrintResult(tree->left);
    }
    if (tree->type == SYMB) {
        printf("%c", *tree->key.symb);
    } else if (tree->type == VAR) {
        printf("%c", *tree->key.symb);
    } else {
        printf("%d", tree->key.num);
    }
    if (tree->right != NULL) {
        PrintResult(tree->right);       
        printf(")");
    }
}

bool IsOperator(char a){
    return (a == '+' || a == '-' || a  == '/' || a == '*' || a == '^');
}

void Do(Node **tree, Stack *num, Stack *var) {
    if (tree == NULL) {
        return;
    }
        if ((*tree)->type != NUM && *(*tree)->key.symb == '+') {
            if ((*tree)->right->type != NUM && *(*tree)->right->key.symb == '+') {
                Do(&(*tree)->right, num, var);
            } else if ((*tree)->right->type == SYMB && *(*tree)->right->key.symb != '+') {
                printf("\n!!!Ошибка, данное действие не входит в сферу моего задания и препятствует его выполнению!!!\n");
                exit(-1);
            }
            if ((*tree)->left->type != NUM && *(*tree)->left->key.symb == '+') {
                Do(&(*tree)->left, num, var);
            } else if ((*tree)->left->type == SYMB && *(*tree)->left->key.symb != '+') {
                printf("\n!!!Ошибка, данное действие не входит в сферу моего задания и препятствует его выполнению!!!\n");
                exit(-1);
            }
            if ((*tree)->left != NULL && (*tree)->left->type == NUM) {
                StackPush(num, (*tree)->left->key.num, NUM);
                (*tree)->left = NULL;
            } else if ((*tree)->left != NULL && (*tree)->left->type == VAR) {
                StackPush(var, *(*tree)->left->key.symb, VAR);
                (*tree)->left = NULL;
            }
            if ((*tree)->right != NULL && (*tree)->right->type == NUM) {
                StackPush(num, (*tree)->right->key.num, NUM);
                (*tree)->right = NULL;
            } else if ((*tree)->right != NULL && (*tree)->right->type == VAR) {
                StackPush(var, *(*tree)->right->key.symb, VAR);
                (*tree)->right = NULL;
            }
            if ((*tree)->left == NULL && (*tree)->right == NULL) {
                (*tree) = NULL;
            }
        } else if ((*tree)->type == SYMB && *(*tree)->key.symb != '+') {
            printf("\n!!!Ошибка, данное действие не входит в сферу моего задания и препятствует его выполнению!!!\n");
            exit(-1);
        }           
}



void StackToTree(Stack *stk, Node *tree) {
    while (stk->top != NULL && (tree->left == NULL || tree->right == NULL)) {
        if (tree->right == NULL) {
            if (stk->top->type == SYMB) {
                tree->right = TreeAdd(tree, StackPop(stk), stk->top->type);
                StackToTree(stk, tree->right);
            } else {
                tree->right = TreeAdd(tree, StackPop(stk), stk->top->type);
            }
        } else {
            if (stk->top->type == SYMB) {
                tree->left = TreeAdd(tree, StackPop(stk), stk->top->type);
                StackToTree(stk, tree->left);
            } else {
                tree->left = TreeAdd(tree, StackPop(stk), stk->top->type);
            }
        }
    }
}

void Stage1(Node* tree) {
    if (tree == NULL) {
        return;
    }
    if (*tree->key.symb == '^') {
        Stack num = StackInit();
        Stack var = StackInit();
        
        Do(&tree->right, &num, &var);
        if (!(StackIsEmpty(&num)) || !(StackIsEmpty(&var))) {
            if (tree->left->type == NUM) {
                int k = tree->left->key.num;
                ForNUM(&tree, &num, &var, k);
            } else if (tree->left->type == VAR) {
                char k = *tree->left->key.symb;
                ForVAR(&tree, &num, &var, k);
            } else {
                Node *k = tree->left;
                ForSYMB(&tree, &num, &var, k);
            }
        }
    }
    //printf("+");
    //TreePrint(tree, 0);
    if (tree->left != NULL && tree->left->type == SYMB) {
        
        //TreePrint(tree, 0);
        Stage1(tree->left);
    }
    if (tree->right != NULL && tree->right->type == SYMB) {
        
        //TreePrint(tree, 0);
        Stage1(tree->right);
    }
    
}

void ReadForm(){
    Stack operators = StackInit();
    Stack values = StackInit();
    char c = ' ';
    while (c != EOF && c != '\n'){
        if (c != ' ') {
            if (IsOperator(c)) {
                switch (c) {
                    case '+':
                        if (StackIsEmpty(&operators) != true) {
                            while (*StackTop(&operators).symb != '(') {
                                StackPush(&values, *StackPop(&operators).symb, SYMB);
                                if (operators.top == NULL) {
                                    break;
                                }
                            }
                            StackPush(&operators, c, SYMB);
                        } else {
                            StackPush(&operators, c, SYMB);
                        }
                        break;
                    case '-':
                        if (StackIsEmpty(&operators) != true) {
                            while (*StackTop(&operators).symb != '(') {
                                StackPush(&values, *StackPop(&operators).symb, SYMB);
                                if (operators.top == NULL) {
                                    break;
                                }
                            }
                            StackPush(&operators, c, SYMB);
                        } else {
                            StackPush(&operators, c, SYMB);
                        }
                        break;
                    case '*':
                        if (StackIsEmpty(&operators) != true) {
                            while (*StackTop(&operators).symb == '*' || *StackTop(&operators).symb == '/' || *StackTop(&operators).symb == '^') {
                                StackPush(&values, *StackPop(&operators).symb, SYMB);
                                if (operators.top == NULL) {
                                    break;
                                }
                            }
                            StackPush(&operators, c, SYMB);
                        } else {
                            StackPush(&operators, c, SYMB);
                        }
                        break;
                    case '/':
                        if (StackIsEmpty(&operators) != true) {
                            while (*StackTop(&operators).symb == '*' || *StackTop(&operators).symb == '/' || *StackTop(&operators).symb == '^') {
                                StackPush(&values, *StackPop(&operators).symb, SYMB);
                                if (operators.top == NULL) {
                                    break;
                                }
                            }
                            StackPush(&operators, c, SYMB);
                        } else {
                            StackPush(&operators, c, SYMB);
                        }
                        break;
                    case '^':
                        if (StackIsEmpty(&operators) != true) {
                            while (*StackTop(&operators).symb == '^') {
                            StackPush(&values, *StackPop(&operators).symb, SYMB);
                            if (operators.top == NULL) {
                                break;
                                }
                            }
                            StackPush(&operators, '^', SYMB);

                        } else {
                            StackPush(&operators, '^', SYMB);
                        }
                        break;

                    default:
                        break;
                }
            }else if (c == '(') {
                StackPush(&operators, c, SYMB);
            } else if (c == ')') {
                while (*StackTop(&operators).symb != '(') {
                    StackPush(&values, *StackPop(&operators).symb, SYMB);
                }
                StackPop(&operators);
            } else if (c >= '0' && c <= '9') {
                int buf = 0;
                while (1) {
                    if (c == ' ' || c == '\n' || c == ')') {
                        break;
                    }
                    buf = buf * 10 + (c - '0');
                    c = getchar();
                }
                StackPush(&values, buf, NUM);
                if (c == ')') {
                    while (*StackTop(&operators).symb != '(') {
                        StackPush(&values, *StackPop(&operators).symb, SYMB);
                    }
                StackPop(&operators);
                }
            } else {
                //printf("ok");
                StackPush(&values, c, VAR);
            }
        } 
    if (c == '\n') {
        break;
    }
    c = getchar();
    }
    while (operators.top != NULL) {
        StackPush(&values, *operators.top->value.symb, SYMB);
        StackPop(&operators);
    }
    StackPrint(&values);
    Node tree;
    tree = *CreateNode(StackPop(&values), SYMB);
    StackToTree(&values, &tree);
    printf("\n\n");

    TreePrint(&tree, 0);
    Stage1(&tree);
    PrintResult(&tree);
}

int main() {
    ReadForm();
}