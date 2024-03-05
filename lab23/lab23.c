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

void FindNodeR(Node *t, int id, Node **res, Node **parent, Node **side) {
    if (t->child != NULL && t->child->id == id) {
        *res = t->child;
        *parent = t;
    } else if (t->side != NULL && t->side->id == id) {
        *res = t->side;
        *side = t;
    } else {
        if (t->side != NULL)
            FindNodeR(t->side, id, res, parent, side);
        if (t->child != NULL)
            FindNodeR(t->child, id, res, parent, side);
    }
}

void FindNode(Tree *t, int id, Node **res, Node **parent, Node **side) {
    *res = NULL;
    *parent = NULL;
    *side = NULL;
    if (t->root->id == id) {
        *res = t->root;
    } else {
        FindNodeR(t->root, id, res, parent, side);
    }
}

int AddNode(Tree *t, int parent_id, int val) {
    Node *new = (Node *)malloc(sizeof(Node));
    new->child = NULL;
    new->side = NULL;
    new->id = (++t->id_counter);
    new->val = val;

    if (t->root == NULL) {
        t->root = new;
        return new->id;
    }

    Node *parent, *p, *s;
    FindNode(t, parent_id, &parent, &p, &s);
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
    Node *n, *p, *s;
    FindNode(t, id, &n, &p, &s);
    if (n == NULL) {
        return; // no such node found
    }
    if (p != NULL)
        p->child = n->side; // if connected vertically
    else if (s != NULL) {
        s->side = n->side; // if connected horizontally
    } else {
        t->root = NULL; // if root element
        t->id_counter = 0;
    }
    if (n->child != NULL)
        RemoveNodeR(n->child);
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
    printf("s: stop\n");
    printf("> ");
    Tree t = {0};
    char c;
    int a, b;
    do {
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
        } else {
            printf("unknown commad %c\n", c);
        }
        printf("> ");
    } while (c != 's');
    printf("\n");
    return 0;
}
