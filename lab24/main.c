#include <stdlib.h>
#include <stdio.h>
#include "stack.h"
#include "tree.h"
#include <stdbool.h>



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

void Make(Node *tree, Stack *new, int *sum) {
    //printf("ok");
    //StackPrint(new);
    //TreePrint(tree, 0);
    if (*sum != 0) {
        if (tree->right == NULL && tree->left == NULL) {
            if (StackIsEmpty(new)) {
                tree->type = NUM;
                tree->key.symb = NULL;
                tree->key.num = *sum;
                tree->right = NULL;
                tree->left = NULL;
            } else {
                if (StackSize(new) == 1) {
                    //printf(" %d ", StackSize(new));
                    //tree->left->type = VAR;
                    //tree->left->key = StackPop(new);
                    //tree->right->type = NUM;
                    //tree->right->key.num = *sum;
                    //StackFree(new);
                    tree->left = TreeAdd(tree, StackPop(new), VAR);
                    StackPush(new, *sum, NUM);
                    tree->right = TreeAdd(tree, StackPop(new), NUM);
                    //printf(" %d ", StackSize(new));
                } else {
                    //printf("YES");
                    tree->left = TreeAdd(tree, StackPop(new), VAR);
                    StackPush(new, '+', SYMB);
                    tree->right = TreeAdd(tree, StackPop(new), SYMB);
                    //tree->right->type = SYMB;
                    //*tree->right->key.symb = '+';
                    Make(tree->right, new, sum);
                }
            }
        } else if (tree->right != NULL) {
            StackPush(new, '+', SYMB);
            tree->left = TreeAdd(tree, StackPop(new), SYMB);
            Make(tree->left, new, sum);
        } else {
            StackPush(new, '+', SYMB);
            tree->right = TreeAdd(tree, StackPop(new), SYMB);
            Make(tree->right, new, sum);
        }
    } else { 
        if (tree->right == NULL && tree->left == NULL) {
            if (StackSize(new) == 1) {
                tree->type = VAR;
                tree->key = StackPop(new);
                //tree->key.num = NULL;
                tree->right = NULL;
                tree->left = NULL;
                //tree = TreeAdd(tree, StackPop(new), VAR);
                //StackPush(new, *sum, NUM);
                //tree->right = TreeAdd(tree, StackPop(new), NUM);
                //printf(" %d ", StackSize(new));
            } else {
                //printf("YES");
                tree->left = TreeAdd(tree, StackPop(new), VAR);
                StackPush(new, '+', SYMB);
                tree->right = TreeAdd(tree, StackPop(new), SYMB);
                //tree->right->type = SYMB;
                //*tree->right->key.symb = '+';
                Make(tree->right, new, sum);
            }
        } else if (tree->right != NULL) {
        StackPush(new, '+', SYMB);
        tree->left = TreeAdd(tree, StackPop(new), SYMB);
            Make(tree->left, new, sum);
        } else {
            StackPush(new, '+', SYMB);
            tree->right = TreeAdd(tree, StackPop(new), SYMB);
            Make(tree->right, new, sum);
        }

    }
    //TreePrint(tree, 0);
}
void Do(Node **tree, int *sum, Stack *new, int *k) {
    if (tree == NULL) {
        return;
    }
    //TreePrint(*tree, 0);
    printf("\n\n");
    //printf("%d ", *k);
    //printf("YES");
    printf("\n\n");
    //if (tree->left != NULL && tree->right != NULL) {
        if ((*tree)->type != NUM && *(*tree)->key.symb == '+') {
            *k += 1;
            if ((*tree)->left->type == NUM) {
                *sum += (*tree)->left->key.num;
                (*tree)->left = NULL;
            }
            if ((*tree)->right->type == NUM) {
                *sum += (*tree)->right->key.num;
                (*tree)->right = NULL;
            }
            //printf("%d ", sum);
            if ((*tree)->right != NULL && (*tree)->right->type == VAR) {
                StackPush(new, *(*tree)->right->key.symb, VAR);
                (*tree)->right = NULL;
            }
            if ((*tree)->left != NULL && (*tree)->left->type == VAR) {
                StackPush(new, *(*tree)->left->key.symb, VAR);
                (*tree)->left = NULL;
            }
            //printf("YES");
            if ((*tree)->left != NULL && *(*tree)->left->key.symb == '+') {
                //printf("YES");
                Do(&(*tree)->left, sum, new, k);
                *k -= 1;
                //printf("%d ", *k);
            }
            //printf("YES");
            if ((*tree)->right != NULL && *(*tree)->right->key.symb == '+') {
                //printf("%d ", k);
                //printf("YES");
                Do(&(*tree)->right, sum, new, k);
                *k -= 1;
            }
            //TreePrint(tree, 0);
            //printf("%d ", *sum);
            // if ((*tree)->left != NULL) {
            //     //printf("fdfdfdfdfdfdf");
            // }
            //printf("YES");
            //TreePrint(tree, 0);
            //printf("%d", *k);
            if ((*k == 0)) {
                //TreePrint(*tree, 0);
                //printf("%c", (*tree)->right);
                if ((*tree)->right == NULL) {
                    //printf("YES++");
                    //printf("YES");
                    
                    Make((*tree), new, sum);
                    return;
                } else if ((*tree)->right == NULL) {
                    //(*tree)Print((*tree)->left, 0);
                    //printf("YES");
                    //(*tree)->right->type = SYMB;
                    //*(*tree)->right->key.symb = '+';
                    StackPush(new, '+', SYMB);
                    (*tree)->right = TreeAdd(*tree, StackPop(new), SYMB);
                    Make((*tree)->right, new, sum);
                    return;
                } else if ((*tree)->right->type == SYMB  && (*tree)->left == NULL) {
                    //printf("YES");
                    StackPush(new, '+', SYMB);
                    (*tree)->left = TreeAdd(*tree, StackPop(new), SYMB);
                    //(*tree)->left->type = SYMB;
                    //*(*tree)->left->key.symb = '+';
                    Make((*tree)->left, new, sum);
                    return;
                }
            } else {
                //printf("YES");;
                if ((*tree)->right == NULL && (*tree)->left == NULL) {
                    *tree = NULL;
                } else if ((*tree)->left != NULL && (*tree)->left->type == SYMB) {
                    //printf("YES");
                    *tree = (*tree)->left;
                } else {
                    *tree = (*tree)->right;
                }
                //*tree = NULL;
                //TreeFree(tree);
                //printf("YES");
                //tree = NULL;
                //TreePrint(*tree, 0);
                //printf("qq%dqq", *k);
                return;
            }
        }
        //printf(" %d ", k);
    //}
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
    if (*tree->key.symb == '+') {
        Stack new = StackInit();
        int k = -1;
        int sum = 0;
        Do(&tree, &sum, &new, &k);
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

    FindMinus(&tree);
    TreePrint(&tree, 0);
    Stage1(&tree);
    //TreePrint(&tree, 0);
    //DeletDividerOne(&tree);
    // printf("\n");
    // TreePrint(&tree, 0);
    PrintResult(&tree);
}

int main() {
    ReadForm();
}