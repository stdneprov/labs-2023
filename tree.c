#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

Tree InitTree() {
    Tree ptr = NULL;
//    printf("Дерево инициализировано\n");
    return ptr;
}

void Clear(Node** targ){
    if (*targ == NULL) {
        return;
    }
    
    Clear(&(*targ)->rvalue);
    Clear(&(*targ)->lvalue);

    free(*targ);
    *targ = NULL;
}

int Add(Node** parent, Value val, enum Type type) {
    Node* ptr = (Node*)malloc(sizeof(Node));
    if (ptr == NULL) {
//        printf("Узел не добавлен, недостаточно памяти\n");
        return 0;
    }
    *parent = ptr;
    ptr->val = val;
    ptr->type = type;
    ptr->lvalue = NULL;
    ptr->rvalue = NULL;
//    printf("Узел добавлен\n");
    return 1;
}

int Del(Node** targ) {
    if (*targ == NULL) {
//        printf("Нет такого узла\n");
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
//    printf("Узел удалён\n");
    return 1;
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
        printf("%c\n", ptr->val.var);
    } else {
        printf("%c\n", ptr->val.oper); 
    }
    if (ptr->lvalue != NULL) {
        PrintTree(ptr->lvalue, depth + 1);
    }
}

void PrintExpression(Node* ptr) {
    if (ptr->lvalue != NULL) {
        PrintExpression(ptr->lvalue);
    }

    switch (ptr->type)
    {
    case NUM:
        printf("%d", ptr->val.num);
        break;

    case OPER:
        if (ptr->lvalue != NULL) {
            printf(" %c ", ptr->val.oper);
        } else {
            printf("%c", ptr->val.oper);
        }
        break;

    case VAR:
        printf("%c", ptr->val.oper);
        break;
    
    default:
        break;
    }

    if (ptr->rvalue != NULL) {
        PrintExpression(ptr->rvalue);
    }
}
