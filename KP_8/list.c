#include"list.h"

List* NewList(){
    List* res = (List*)malloc(sizeof(List));
    if (res == NULL) {
        exit(-1);
    }
    res->head = NULL;
    res->size = 0;
    return res;
}

Node* CreatedNode(Complex val){
    Node* res = (Node*)malloc(sizeof(Node));
    if (res == NULL) {
        exit(-1);
    }
    res->next = NULL;
    res->val = val;
    return res;
}

void RFree(Node* now, Node* head){
    if (now->next == head){
        free(now);
        return;
    }
    RFree(now->next, head);
    free(now);
}

void FreeList(List* l){
    if (l->head != NULL) {
        RFree(l->head, l->head);
    } 
    free(l);
}

void RInsert(Node* now, Node* head, Complex a){
    if (now->next == head){
        now->next = CreatedNode(a);
        now->next->next = head;
        return;
    }
    RInsert(now->next, head, a);
}

void Insert(List* l, Complex a){
    l->size++;
    if (l->head == NULL){
        l->head = CreatedNode(a);
        l->head->next = l->head;
        return;
    }
    RInsert(l->head, l->head, a);
}

void RPrint(Node* now, Node* head){
    printf("%lg ", now->val.re);
    printf("%lg  ", now->val.im);
    if (now->next != head) {
        RPrint(now->next, head);
    } 
}

void Print(List* l){
    if (l->head != NULL) {
        RPrint(l->head, l->head);
    } else {
        printf("List is empty");
    }
    printf("\n");
}

Node* RFind(Node* now, Node* head, Complex a){
    if (now->next->val.im == a.im) {
        if (now->next->val.re == a.re) {
            return now;
        }
        
    }
    if (now->next == head) {
        return NULL;
    } 
    return RFind(now->next, head, a);
}

Node* FindPrev(List* l, Complex a){
    if (l->head != NULL) {
        return RFind(l->head, l->head, a);
    } 
    else {
        return NULL;
    }
}
void Erase(List* l, Complex a){
    Node* now = FindPrev(l, a);
    if (now == NULL){
        printf("Can`t find\n");
        return;
    }
    if (now->next == l->head){
        if (l->size == 1){
            free(l->head);
            l->head = NULL;
        }
        else {
            // Node* temp = l->head;
            l->head = l->head->next;
            now->next = l->head;
            // free(temp);
        }
    }
    else{
        Node* temp = now->next;
        now->next = temp->next;
        free(temp);
    }
    l->size--;
}


void SwapElements(List* l, Complex b, Complex c){
    // printf("\n %lg \n", b.im);

    // printf("\n %lg \n", c.re);
    if (l->head == NULL) {
        printf("List is empty\n");
        return;
    } else {
        Complex tmp;
        tmp.re = b.re;
        tmp.im = b.im;

        Node* elem_b = l->head;
        Node* elem_c = l->head;
        while ((elem_b->val.im != b.im) && (elem_b->val.re != b.re)) {
            if (elem_b->next == l->head) {
                printf("Value not find\n");
                return;
            }
            elem_b = elem_b->next;
        }
        while ((elem_c->val.im != c.im) && (elem_c->val.re != c.re)) {
            if (elem_c->next == l->head) {
                printf("Value not find\n");
                return;
            }
            elem_c = elem_c->next;
        }

        // printf("\n b:re %lg \n", elem_b->val.re);
        // printf("\n c:im %lg \n", elem_c->val.im);

        elem_b->val.im = c.im;
        elem_b->val.re = c.re;


        // b.re = c.re;
        elem_c->val.im = tmp.im;
        elem_c->val.re = tmp.re;


        return;

    }
}
