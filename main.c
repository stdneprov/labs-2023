#include <stdlib.h>
#include <stdio.h>
#include "stack.h"
#include "tree.h"
#include <stdbool.h>

void Stage6(Node **tree) {
    if ((*tree)->left->left != NULL && (*tree)->left->left->type == NUM && (*tree)->left->left->key.num == 1) {
        (*tree)->left = (*tree)->left->right;
    }
    if ((*tree)->right->left != NULL && (*tree)->right->left->type == NUM && (*tree)->right->left->key.num == 1) {
        (*tree)->right = (*tree)->right->right;
    }
}

void Stage5(Node **t, Stack *stk) {
    if (stk->len == 1) {
        (*t)->type = VAR;
        Stack m = StackInit();
        StackPush(&m, *stk->top->value.symb, VAR);
        StackPop(stk);
        (*t)->key = StackPop(&m);
        (*t)->left = (*t)->right = NULL;
    } else {
        (*t)->type = SYMB;
        Stack m = StackInit();
        StackPush(&m, '*', SYMB);
        (*t)->key = StackPop(&m);
        StackPush(&m, *stk->top->value.symb, VAR);
        StackPop(stk);
        Node *pz = (Node *)malloc(sizeof(Node));
        pz->type = SYMB;
        pz->key = StackPop(&m);
        pz->left = pz->right = NULL;
        (*t)->left = pz;
        Node *help = (Node *)malloc(sizeof(Node));
        Stage5(&help, stk);
        (*t)->right = help;
    }
}

void Stage4(Node **tree, Stack *left, Stack *right) {
    if (!(StackIsEmpty(left))) {
        Node *l = (Node *)malloc(sizeof(Node));
        Stage5(&l, left);
        Node *l2 = (Node *)malloc(sizeof(Node));
        Stack h1 = StackInit();
        StackPush(&h1, '*', SYMB);
        l2->key = StackPop(&h1);
        l2->type = SYMB;
        l2->left = (*tree)->left;
        l2->right = l;
        (*tree)->left = l2;

    }
    if (!(StackIsEmpty(right))) {
        Node *r = (Node *)malloc(sizeof(Node));
        Stage5(&r, right);
        Node *r2 = (Node *)malloc(sizeof(Node));
        Stack h2 = StackInit();
        StackPush(&h2, '*', SYMB);
        r2->key = StackPop(&h2);
        r2->type = SYMB;
        r2->left = (*tree)->right;
        r2->right = r;
        (*tree)->right = r2;
    }
}

int NOD(int a, int b) {
    while (a != b) {
        if (a > b) {
            a -= b;
        } else {
            b -= a;
        }
    }
    return a;
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

void SimDelete(Stack *left, Stack *right) {
    if (StackIsEmpty(left) || StackIsEmpty(right)) {
        return;
    }
    int k = 0;
    //StackPrint(right);
    Stack ql = StackInit();
    Stack qr = StackInit();
    while (!(StackIsEmpty(left))) {
        if (StackIsEmpty(&qr)) {
            while (!(StackIsEmpty(right))) {
                //printf("&&%c %c&&\n", *left->top->value.symb, *right->top->value.symb);
                if (*left->top->value.symb == *right->top->value.symb) {
                    StackPop(left);
                    StackPop(right);
                    k = 1;
                    if ((StackIsEmpty(left))) {
                        break;
                    }
                } else {
                    StackPush(&qr, *right->top->value.symb, VAR);
                    StackPop(right);                    
                }
            }
        } else {
            while (!(StackIsEmpty(&qr))) {
                //StackPrint(&qr);
                //printf("+");
                //printf("&&%c %c&&", *left->top->value.symb, *qr.top->value.symb);
                if (*left->top->value.symb == *qr.top->value.symb) {
                    StackPop(&qr);
                    StackPop(left);
                    k = 1;
                } else {
                    StackPush(right, *qr.top->value.symb, VAR);
                    StackPop(&qr);
                }
            }
        }
        if (!(StackIsEmpty(left)) && k == 0) {
            StackPush(&ql, *left->top->value.symb, VAR);
            StackPop(left);
        }
        k = 0;
    }
    while (!(StackIsEmpty(&ql))) {
        StackPush(left, *ql.top->value.symb, VAR);
        StackPop(&ql);
    }
    while (!(StackIsEmpty(&qr))) {
        StackPush(right, *qr.top->value.symb, VAR);
        StackPop(&qr);
    }
}

void TwoStoreyFractionDelete(Node **tree) {
    if (tree == NULL) {
        return;
    }
        if ((*tree)->type != NUM && *(*tree)->key.symb == '/') { 
            if ((*tree)->left->type != NUM && (*tree)->right->type != NUM && *(*tree)->left->key.symb == '/' && *(*tree)->right->key.symb == '/') {
                *(*tree)->left->key.symb = '*';
                *(*tree)->right->key.symb = '*';
                Node *tmp = (Node *)malloc(sizeof(Node));
                Node *mtp = (Node *)malloc(sizeof(Node));
                tmp = (*tree)->left->right;
                mtp = (*tree)->right->right;
                (*tree)->left->right = mtp;
                (*tree)->right->right = tmp;
            } else if ((*tree)->left->type != NUM && *(*tree)->left->key.symb == '/') {
                Node *tmp = (Node *)malloc(sizeof(Node));
                Node *mtp = (Node *)malloc(sizeof(Node));
                tmp = (*tree)->left->right;
                (*tree)->left = (*tree)->left->left;
                Stack a = StackInit();
                StackPush(&a, '*', SYMB);
                mtp->key = StackPop(&a);
                mtp->type = SYMB;
                mtp->left = (*tree)->right;
                mtp->right = tmp;
                (*tree)->right = mtp;
            } else if ((*tree)->right->type != NUM && *(*tree)->right->key.symb == '/') {
                Node *tmp = (Node *)malloc(sizeof(Node));
                Node *mtp = (Node *)malloc(sizeof(Node));
                tmp = (*tree)->right->right;
                (*tree)->right = (*tree)->right->left;
                Stack a = StackInit();
                StackPush(&a, '*', SYMB);
                mtp->key = StackPop(&a);
                mtp->type = SYMB;
                mtp->left = (*tree)->left;
                mtp->right = tmp;
                (*tree)->left = mtp;
            }
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

void Stage3(Node **tree, int numright, int numleft) {
    int nod;
    nod = NOD(numleft, numright);
    numleft = numleft / nod;
    numright = numright / nod;
    if (numright != 1) {
        if ((*tree)->right != NULL) {
            Node *std = (Node *)malloc(sizeof(Node));
            Node *std1 = (Node *)malloc(sizeof(Node));
            Stack h = StackInit();
            StackPush(&h, '*', SYMB);
            std->key = StackPop(&h);
            std->type = SYMB;
            StackPush(&h, numright, NUM);
            std1->key = StackPop(&h);
            std1->type = NUM;
            std1->left = NULL;
            std1->right = NULL;
            std->right = (*tree)->right;
            std->left = std1;
            (*tree)->right = std;
            
        } else {
            Node *std = (Node *)malloc(sizeof(Node));
            Stack h = StackInit();
            StackPush(&h, numright, NUM);
            std->key = StackPop(&h);
            std->type = NUM;
            std->left = NULL;
            std->right = NULL;
            (*tree)->right = std;
        }
        
    }
    if (numleft != 1) {
        if ((*tree)->left != NULL) {
            Node *tsd = (Node *)malloc(sizeof(Node));
            Node *tsd1 = (Node *)malloc(sizeof(Node));
            Stack h = StackInit();
            StackPush(&h, '*', SYMB);
            tsd->key = StackPop(&h);
            tsd->type = SYMB;
            StackPush(&h, numleft, NUM);
            tsd1->key = StackPop(&h);
            tsd1->type = NUM;
            tsd1->left = NULL;
            tsd1->right = NULL;
            tsd->right = (*tree)->left;
            tsd->left = tsd1;
            (*tree)->left = tsd;
            
        } else {
            Node *tsd = (Node *)malloc(sizeof(Node));
            Stack h = StackInit();
            StackPush(&h, numleft, NUM);
            tsd->key = StackPop(&h);
            tsd->type = NUM;
            tsd->left = NULL;
            tsd->right = NULL;
            (*tree)->left = tsd;
        }
        
    }
    if ((*tree)->left == NULL) {
        //printf("+");
        Node *std = (Node *)malloc(sizeof(Node));
        Stack h = StackInit();
        StackPush(&h, numleft, NUM);
        std->key = StackPop(&h);
        std->type = NUM;
        std->left = NULL;
        std->right = NULL;
        (*tree)->left = std;
    }
    if ((*tree)->right == NULL) {
        Node *std1 = (Node *)malloc(sizeof(Node));
        Stack h = StackInit();
        StackPush(&h, numright, NUM);
        std1->key = StackPop(&h);
        std1->type = NUM;
        std1->left = NULL;
        std1->right = NULL;
        (*tree)->right = std1;
    }
}

void Stage1(Node* tree) {
    if (tree == NULL) {
        return;
    }
    if (tree->right != NULL) {
        Stage1(tree->right);
    }
    if (tree->right != NULL) {
        Stage1(tree->left);
    }
    TwoStoreyFractionDelete(&tree);
}

void RebuildTree(Node **tree, Stack *stk, int *num) {
    if ((*tree)->left != NULL && (*tree)->left->type == SYMB && *(*tree)->left->key.symb == '*') {
        RebuildTree(&(*tree)->left, stk, num);
    }
    if ((*tree)->right != NULL && (*tree)->right->type == SYMB && *(*tree)->right->key.symb == '*') {
        RebuildTree(&(*tree)->right, stk, num);
    }
    if ((*tree)->left != NULL && (*tree)->left->type == NUM) {
        *num *= (*tree)->left->key.num;
        (*tree)->left = NULL;
    } else if ((*tree)->left != NULL && (*tree)->left->type == VAR) {
        StackPush(stk, *(*tree)->left->key.symb, VAR);
        (*tree)->left = NULL;
    }
    if ((*tree)->right != NULL && (*tree)->right->type == NUM) {
        *num *= (*tree)->right->key.num;
        (*tree)->right = NULL;
    } else if ((*tree)->right != NULL && (*tree)->right->type == VAR) {
        StackPush(stk, *(*tree)->right->key.symb, VAR);
        (*tree)->right = NULL;
    }
    if ((*tree)->left == NULL && (*tree)->right == NULL) {
        (*tree) = NULL;
        return;
    }
    if ((*tree)->left == NULL) {
        (*tree) = (*tree)->right;
        return;
    }
    if ((*tree)->right == NULL) {
        (*tree) = (*tree)->left;
    }
}


void Task(Node **tree) {
    if ((*tree)->left->type == SYMB && (*(*tree)->left->key.symb == '+' || *(*tree)->left->key.symb == '-' || *(*tree)->left->key.symb == '^')) {
        return;
    }
    if ((*tree)->right->type == SYMB && (*(*tree)->right->key.symb == '+' || *(*tree)->right->key.symb == '-' || *(*tree)->right->key.symb == '^')) {
        return;
    }
    Stack varleft = StackInit();
    int numleft = 1;
    if ((*tree)->left->type == SYMB && *(*tree)->left->key.symb == '*') {
        RebuildTree(&(*tree)->left, &varleft, &numleft);
    }
    Stack varright = StackInit();
    int numright = 1;
    if ((*tree)->right->type == SYMB && *(*tree)->right->key.symb == '*') {
        RebuildTree(&(*tree)->right, &varright, &numright);
    }
    if ((*tree)->left != NULL) {
        if ((*tree)->left->type == NUM) {
            numleft *= (*tree)->left->key.num;
            (*tree)->left = NULL;
        } else if ((*tree)->left->type == VAR) {
            StackPush(&varleft, *(*tree)->left->key.symb, VAR);
            (*tree)->left = NULL;
        }
    }
    if ((*tree)->right != NULL) {
        if ((*tree)->right->type == NUM) {
            numright *= (*tree)->right->key.num;
            (*tree)->right = NULL;
        } else if ((*tree)->right->type == VAR) {
            StackPush(&varright, *(*tree)->right->key.symb, VAR);
            (*tree)->right = NULL;
        }
    }
    
    Stage3(&(*tree), numright, numleft);
    SimDelete(&varleft, &varright);
    Stage4(&(*tree), &varleft, &varright);
    if ((*tree)->left->type == NUM && (*tree)->right->type == NUM && (*tree)->right->key.num == (*tree)->left->key.num) {
        (*tree)->left = (*tree)->right = NULL;
        Stack a = StackInit();
        StackPush(&a, 1, NUM);
        (*tree)->key = StackPop(&a);
        (*tree)->type = NUM;
    }
    if ((*tree)->type == SYMB && (*tree)->left->type == NUM && (*tree)->right->type == NUM && (*tree)->right->key.num == 1) {
        Stack a = StackInit();
        StackPush(&a, (*tree)->left->key.num, NUM);
        (*tree)->key = StackPop(&a);
        (*tree)->type = NUM;
        (*tree)->left = (*tree)->right = NULL;
    }
    Stage6(&(*tree));

}

void Stage2(Node* tree) {
    if (tree == NULL) {
        return;
    }
    if (tree->type == SYMB && *tree->key.symb == '/') {
        Task(&tree);
    }
    if (tree->right != NULL) {
        Stage2(tree->right);
    }
    if (tree->right != NULL) {
        Stage2(tree->left);
    }
    
}


void FindMinus(Node* tree) {
   if (tree == NULL) {
        return;
    }
    if (*tree->key.symb == '-') {
        if ((tree->left == NULL && tree->right->type == NUM)) {
            tree->type = NUM;
            tree->key.symb = NULL;
            tree->key.num = -(tree->right->key.num);
            tree->right = NULL;
            tree->left = NULL; 
        } else if ((tree->right == NULL && tree->left->type == NUM)) {
            tree->type = NUM;
            tree->key.symb = NULL;
            tree->key.num = -(tree->left->key.num);
            tree->right = NULL;
            tree->left = NULL; 
        }
    }
    if (tree->left != NULL && tree->left->type == SYMB) {
        FindMinus(tree->left);
    }
    if (tree->right != NULL && tree->right->type == SYMB) {
        FindMinus(tree->right);
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
    Stage2(&tree);
    PrintResult(&tree);
}

int main() {
    ReadForm();
}