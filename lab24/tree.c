#include "tree.h"

#include <stdio.h>
#include <stdlib.h>

Tree InitTree() {
    Tree ptr = NULL;
    return ptr;
}

void Clear(TreeNode** targ) {
    if (*targ == NULL) {
        return;
    }

    Clear(&(*targ)->rvalue);
    Clear(&(*targ)->lvalue);

    free(*targ);
    *targ = NULL;
}

int AddInTree(TreeNode** parent, ValueStackNode val, enum TypeStackNode type,
              int priority, int sign) {
    TreeNode* ptr = (TreeNode*)malloc(sizeof(TreeNode));
    if (ptr == NULL) {
        return 0;
    }
    *parent = ptr;
    ptr->val = val;
    ptr->type = type;
    ptr->priority = priority;
    ptr->lvalue = NULL;
    ptr->rvalue = NULL;
    ptr->sign = sign;
    return 1;
}

int DeleteTree(TreeNode** targ) {
    if (*targ == NULL) {
        return 0;
    }

    if ((*targ)->rvalue != NULL) {
        Clear(&(*targ)->rvalue);
    }

    if ((*targ)->lvalue != NULL) {
        Clear(&(*targ)->lvalue);
    }

    free(*targ);
    *targ = NULL;
    return 1;
}

TreeNode* GetCharNode(char chr) {
    TreeNode* tmp = (TreeNode*)malloc(sizeof(TreeNode));
    tmp->lvalue = NULL;
    tmp->rvalue = NULL;
    tmp->val.letter = chr;
    tmp->priority = GetPriority(chr);
    if (GetPriority(chr) >= 0) {
        tmp->type = OPERATOR;
    } else {
        tmp->type = VAR;
    }
    return tmp;
}
TreeNode* GetIntNode(int value) {
    TreeNode* tmp = (TreeNode*)malloc(sizeof(TreeNode));
    tmp->lvalue = NULL;
    tmp->rvalue = NULL;
    tmp->val.num = value;
    tmp->type = NUM;
    tmp->priority = -1;
    return tmp;
}

void PrintTree(Tree ptr, int depth) {
    if (ptr->rvalue != NULL) {
        PrintTree(ptr->rvalue, depth + 1);
    }

    for (int i = 0; i < depth; ++i) {
        printf("    ");
    }

    if (ptr->type == 1) {
        printf("%d\n", ptr->val.num);
    } else if (ptr->type == 2) {
        printf("%c\n", ptr->val.letter);
    } else {
        printf("%c\n", ptr->val.letter);
    }
    if (ptr->lvalue != NULL) {
        PrintTree(ptr->lvalue, depth + 1);
    }
}

void PrintInLine(TreeNode* ptr) {
    if (ptr->lvalue != NULL) {
        if (ptr->lvalue->type == OPERATOR &&
            (ptr->priority > ptr->lvalue->priority)) {
            printf("(");
            PrintInLine(ptr->lvalue);
            printf(")");
        } else {
            PrintInLine(ptr->lvalue);
        }
    }

    switch (ptr->type) {
        case NUM:
            if (ptr->sign == -1) {
                printf("-");
            }
            printf("%d", ptr->val.num);
            break;

        case OPERATOR:
            if (ptr->lvalue != NULL) {
                printf(" %c ", ptr->val.letter);
            } else {
                printf("%c", ptr->val.letter);
            }
            break;

        case VAR:
            if (ptr->sign == -1) {
                printf("-");
            }
            printf("%c", ptr->val.letter);
            break;

        default:
            break;
    }

    if (ptr->rvalue != NULL) {
        if (ptr->rvalue->type == OPERATOR &&
            (ptr->priority > ptr->rvalue->priority)) {
            printf("(");
            PrintInLine(ptr->rvalue);
            printf(")");
        } else {
            PrintInLine(ptr->rvalue);
        }
    }
}

void StackToTree(Stack* expr, TreeNode** node) { /* Из стека в дерево */
    if (expr->size == 0) {
        printf("Something wrong\n");
        return;
    }
    Node elem = StackPop(expr);

    if (elem.type == OPERATOR) {
        AddInTree(node, elem.val, elem.type, elem.priority, elem.sign);
        StackToTree(expr, &((*node)->rvalue));

        if (elem.priority >= 0) {  // минус
            StackToTree(expr, &((*node)->lvalue));
        }
    } else {
        AddInTree(node, elem.val, elem.type, elem.priority, elem.sign);
    }
}

int FindMulti(TreeNode* node) {
    if (node->type == NUM) {
        return node->val.num;
    }
    if (node->type == VAR) {
        return 1;
    }
    int ans = 1;
    if (node->lvalue->type == NUM) {
        ans *= node->lvalue->val.num;
    } else if (node->lvalue->val.letter == '*') {
        ans *= FindMulti(node->lvalue);
    }
    if (node->rvalue->type == NUM) {
        ans *= node->rvalue->val.num;
    } else if (node->rvalue->val.letter == '*') {
        ans *= FindMulti(node->rvalue);
    }
    return ans;
}

void DivNode(TreeNode* node, int* target) {
    int curTrg = *target;
    if (*target == 1) {
        return;
    }
    if (node->type == NUM) {
        int delitel = gcd(node->val.num, curTrg);
        node->val.num /= delitel;
        *target /= delitel;
        return;
    }
    if (node->val.letter != '*') {
        return;
    }
    if (node->lvalue->type == NUM) {
        int delitel = gcd(node->lvalue->val.num, curTrg);
        node->lvalue->val.num /= delitel;
        *target /= delitel;
    } else if (node->lvalue->val.letter == '*') {
        DivNode(node->lvalue, target);
    }
    if (node->rvalue->type == NUM) {
        int delitel = gcd(node->rvalue->val.num, curTrg);
        node->rvalue->val.num /= delitel;
        *target /= delitel;
    } else if (node->rvalue->val.letter == '*') {
        DivNode(node->rvalue, target);
    }
}

int FindVar(TreeNode* node, char target) {
    if (node->type == NUM) {
        return 0;
    } else if (node->type == VAR && node->val.letter == target) {
        return 1;
    } else if (node->type == VAR && node->val.letter != target) {
        return 0;
    }
    if (node->val.letter != '*') {
        return 0;
    }
    return FindVar(node->lvalue, target) || FindVar(node->rvalue, target);
}

void DelOneMulti(Tree* tree) {
    if (*tree == NULL) {
        return;
    }
    if ((*tree)->type == OPERATOR && (*tree)->val.letter == '*') {
        if ((*tree)->lvalue->type == NUM && (*tree)->lvalue->val.num == 1) {
            TreeNode* toDel = (*tree)->lvalue;
            (*tree) = (*tree)->rvalue;
            free(toDel);
        } else if ((*tree)->rvalue->type == NUM &&
                   (*tree)->rvalue->val.num == 1) {
            TreeNode* toDel = (*tree)->rvalue;
            (*tree) = (*tree)->lvalue;
            free(toDel);
        }
    }
    DelOneMulti(&(*tree)->lvalue);
    DelOneMulti(&(*tree)->rvalue);
}

void VariantTree(Tree* tree) {
    if (*tree == NULL) {
        return;
    }
    if ((*tree)->type != OPERATOR) {
        return;
    }
    VariantTree(&(*tree)->lvalue);
    DelOneMulti(tree);
    VariantTree(&(*tree)->rvalue);
    DelOneMulti(tree);

    if ((*tree)->type == OPERATOR && (*tree)->val.letter == '-') {
        int rv, lv;
        if ((*tree)->lvalue->type == NUM) {
            lv = (*tree)->lvalue->val.num;
        } else if ((*tree)->lvalue->type == OPERATOR &&
                   (*tree)->lvalue->val.letter == '*') {
            lv = FindMulti((*tree)->lvalue);
        } else {
            return;
        }

        if ((*tree)->rvalue->type == NUM) {
            rv = (*tree)->rvalue->val.num;
        } else if ((*tree)->rvalue->type == OPERATOR &&
                   (*tree)->rvalue->val.letter == '*') {
            rv = FindMulti((*tree)->rvalue);
        } else {
            return;
        }
        int nod = gcd(lv, rv);
        if (nod == 1) {
            return;
        }
        int lDel = nod;
        int rDel = nod;
        TreeNode* newParentNode = GetCharNode('*');
        newParentNode->lvalue = GetIntNode(nod);
        DivNode((*tree)->lvalue, &lDel);
        DivNode((*tree)->rvalue, &rDel);
        newParentNode->rvalue = *tree;
        *tree = newParentNode;
        DelOneMulti(tree);
    }
}

void VariantTreeVar(Tree* tree) {
    int flag = 0;
    if ((*tree)->type != OPERATOR) {
        return;
    }
    VariantTreeVar(&(*tree)->lvalue);
    DelOneMulti(tree);
    VariantTreeVar(&(*tree)->rvalue);
    DelOneMulti(tree);

    if ((*tree)->type == OPERATOR && (*tree)->val.letter == '-') {
        // char varToMulti;
        for (char i = 'a'; i <= 'z'; i++) {
            if (FindVar((*tree)->lvalue, i) && FindVar((*tree)->rvalue, i)) {
                VarOutside(tree, i);
                DelOneMulti(tree);
                flag = 1;
            }
        }
    }
    if (flag) {
        VariantTreeVar(tree);
    }
}

void VarOutside(Tree* tree, char target) {
    TreeNode* newParentNode = GetCharNode('*');
    newParentNode->lvalue = GetCharNode(target);
    char lDel = target;
    char rDel = target;
    DivNodeByVar((*tree)->lvalue, &lDel);
    DivNodeByVar((*tree)->rvalue, &rDel);
    newParentNode->rvalue = *tree;
    *tree = newParentNode;
}

void DivNodeByVar(TreeNode* node, char* target) {
    char curTrg = *target;
    if (*target == 1 || node->type == NUM) {
        return;
    }
    if (node->type == VAR) {
        if (node->val.letter == curTrg) {
            *target = 1;
            TreeNode* tmp = GetIntNode(1 * node->sign);
            *node = *tmp;
            free(tmp);
            return;
        } else {
            return;
        }
    }
    if (node->val.letter == '*') {
        DivNodeByVar(node->lvalue, target);
        DivNodeByVar(node->rvalue, target);
    }
}