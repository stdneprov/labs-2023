#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node Node;
typedef struct Tree Tree;

struct Tree {
    int id_counter;
    Node *root;
};

struct Node {
    int id;
    int val;
    Node *child;
    Node *side;
};

void FindNode(Node *t, int id, Node **res, Node **prev) {
    if (t == NULL || *res != NULL) {
        return;
    }
    if (t->id == id) {
        *res = t;
        return;
    }
    *prev = t;
    FindNode(t->side, id, res, prev);
    *prev = t;
    FindNode(t->child, id, res, prev);
}

int AddNode(Tree *t, int parent_id, int val) {
    Node *new = (Node *)malloc(sizeof(Node));
    if (new == NULL) {
        printf("ERROR: Not enought memory\n");
        exit(1);
    }
    new->child = NULL;
    new->side = NULL;
    new->id = (++t->id_counter);
    new->val = val;

    if (t->root == NULL) {
        t->root = new;
        return new->id;
    }

    Node *parent = 0, *prev = 0;
    FindNode(t->root, parent_id, &parent, &prev);
    if (parent == NULL) {
        printf("ERROR: no node with id %d found\n", parent_id);
        exit(1);
        return 0;
    }
    if (parent->child == NULL) {
        parent->child = new;
    } else {
        parent = parent->child;
        while (parent->side != NULL) {
            parent = parent->side;
        }
        parent->side = new;
    }
    return new->id;
}

void RemoveNodeR(Node *n) {
    if (n->child != NULL)
        RemoveNodeR(n->child);
    if (n->side != NULL)
        RemoveNodeR(n->side);
    free(n);
}

void RemoveNode(Tree *t, int id) {
    Node *n = 0, *p = 0;
    FindNode(t->root, id, &n, &p);
    if (n == NULL) {
        return; // no such node found
    }
    if (p == NULL) {
        t->root = NULL; // if root element
        t->id_counter = 0;
    } else if (p->child == n)
        p->child = n->side; // if connected vertically
    else if (p->side == n) {
        p->side = n->side; // if connected horizontally
    }
    if (n->child != NULL)
        RemoveNodeR(n->child);
    free(n);
}

void PrintTreeR(Node *n, int offset) {
    while (n != NULL) {
        for (int i = 0; i < offset * 4; i++)
            printf(" ");
        printf("%d:%d\n", n->id, n->val);
        PrintTreeR(n->child, offset + 1);
        n = n->side;
    }
}

void PrintTree(Tree *t) {
    if (t->root != NULL)
        PrintTreeR(t->root, 0);
}

void DeepestNonEndValueR(Node *n, int depth, int *max, int *res) {
    if (n->child != NULL && depth >= *max) {
        *res = n->val;
        *max = depth;
    }
    if (n->child != NULL)
        DeepestNonEndValueR(n->child, depth + 1, max, res);
    if (n->side != NULL)
        DeepestNonEndValueR(n->side, depth, max, res);
}

// Определить значение нетерминальной вершины дерева с максимальной глубиной.
int DeepestNonEndValue(Tree *t) {
    int res = 0;
    int max = 0;
    if (t->root == 0) {
        printf("ERROR: The tree is empty\n");
        exit(1);
    }
    DeepestNonEndValueR(t->root, 0, &max, &res);
    return res;
}

int main(void) {
    printf("a i v:\t create new node with parent i and value v\n");
    printf("r id:\t remove node vith id i\n");
    printf("p: print\n");
    printf("d: deepest nonterminal value\n");
    printf("q: quit\n");
    printf("> ");
    Tree t = {0};
    char c;
    int a, b;
    while (true) {
        scanf("%c", &c);
        if (c == '\n') {
            continue;
        }
        if (c == 'a') {
            scanf("%d %d", &a, &b);
            AddNode(&t, a, b);
        } else if (c == 'r') {
            scanf("%d", &a);
            RemoveNode(&t, a);
        } else if (c == 'p') {
            PrintTree(&t);
        } else if (c == 'd') {
            printf("%d\n", DeepestNonEndValue(&t));
        } else if (c == 'q') {
            return 0;
        } else {
            printf("unknown commad %c\n", c);
        }
        printf("> ");
    }
    printf("\n");
    return 0;
}
