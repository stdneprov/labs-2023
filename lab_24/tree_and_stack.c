#include "tree_and_stack.h"


struct Token Pop(struct Stack* q){
    if(!q->size){
        struct Token tok;
        return tok;
    }
    return q->nodes[--q->size];
}

void InitStack(struct Stack* q){
    q->capacity = 2; //выделяем под 2 элемента
    q->size = 0;
    q->nodes = (struct Token*)malloc(sizeof (struct Token)*q->capacity);
}

void PushBack(struct Stack* q, struct Token element){
    //если лишнего места уже нет, то его нужно добавить
    if(q->size == q->capacity){
        q->capacity *= 2;
        q->nodes = (struct Token*)realloc(q->nodes, sizeof(struct Token) * q->capacity ); //повышаем резерв
    }
    q->nodes[q->size++] = element;
}

//вершина
struct Token Peak(struct Stack* q) {
    return q->nodes[q->size - 1];
}

//приоритет операций
int PriorityOfOperation(char a) {
    if (a == '+' || a == '-') {
        return 0;
    }
    if (a == '*' || a == '/') {
        return 1;
    }
    return 2;
}

void PrintStack(struct Stack* s) {
    for (int i = 0; i < s->size; i++) {
        //если операция
        if (s->nodes[i].tokentype == 0) {
            printf("%c ", s->nodes[i].operation);
        } else if (s->nodes[i].tokentype == 1) { //если число
            printf("%u ",s->nodes[i].value);
        } else printf("%c ",s->nodes[i].operation); //если операция
    }
    printf("\n");
}

void InitTree(struct Tree* t) {
    t->root = NULL;
}

struct Node* SubInsert(struct Node* node, struct Stack* s){
    if (node == NULL) {
            node = (struct Node*)malloc(sizeof(struct Node));
            node->object = Pop(s);
            node->left = NULL;
            node->right = NULL;
            if (node->object.tokentype == 1 || node->object.tokentype == 2) {
                return node;
            }
    }
    if (!node->right || (node->right && node->right->object.tokentype == 0)) {
            node->right = SubInsert(node->right, s);
    }
    if (!node->left || (node->left && node->left->object.tokentype == 0)) {
            node->left = SubInsert(node->left, s);
    }
    return node;
}

void Insert(struct Tree* t, struct Stack* s) {
    if (!t->root){
        t->root = (struct Node*)malloc(sizeof(struct Node));
        t->root->object = Pop(s);
        t->root->right=NULL;
        t->root->left=NULL;
    }
    //если что-то есть
    if (s->size > 0) {
        t->root = SubInsert(t->root, s);
    }
}

//выводы
void PrintElement(struct Token element) {
    if (element.tokentype == 0) {
        printf("%c",element.operation);
    }
    else if (element.tokentype == 1 ) {
        printf("%u",element.value);
    } else printf("%c",element.operation);
}

void PrintTree(struct Node* node) {
    if(!node->left && !node->right) {
        PrintElement(node->object);
        return;
    }
    if(node->left) {
        PrintTree(node->left);
    }
    PrintElement(node->object);
    if(node->right) {
        PrintTree(node->right);
    }
}

//чистим память
void SubFreeTree(struct Tree* t,struct Node* node) {
    if(!node->left && !node->right) {
        free(node);
        return;
    }
    if(node->left) {
        SubFreeTree(t,node->left);
    }
    if(node->right) {
        SubFreeTree(t,node->right);
    }
    free(node);
}

void FreeTree(struct Tree* t) {
    if (t->root->left) {
        SubFreeTree(t,t->root->left);
    }
    if (t->root->right) {
        SubFreeTree(t,t->root->right);
    }
    free(t->root);
}


