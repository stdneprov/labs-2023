#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<stdbool.h>



typedef struct node 
{
	int data; 
	unsigned char height; 

	struct node* left; 
	struct node* right;
} node;


node* create_node(int data) {
	
    struct node* node = (struct node*)malloc(sizeof(struct node)); 
	
    node->data = data;

    node->left = NULL;
    node->right = NULL;
    

	node->height = 1;

    return node; 
}

//
unsigned char height(node* p) {

	if(p != NULL) {
		return p->height;
	} else {
		return 0;
	}
	
}

int bfactor(node* p) {
	
	return height(p->right) - height(p->left);
	
}


void fixheight(node* p) {
	
	unsigned char hl = height(p->left);
	unsigned char hr = height(p->right);

	
	p->height = (hl > hr ? hl : hr) + 1;
}

// функции вращения
node* rotateright(node* p) {
	
	node* q = p->left; 
	p->left = q->right; 
	q->right = p;


	fixheight(p);
	fixheight(q);

	
	return q;
}
node* rotateleft(node* q) 
{
	node* p = q->right;

	q->right = p->left;
	p->left = q;
	
	fixheight(q);
	fixheight(p);
	
	return p;
}


node* balance(node* p) {

	fixheight(p); 

	
	if (bfactor(p) == 2) {
		if( bfactor(p->right) < 0 ) {
			p->right = rotateright(p->right);
		}
		return rotateleft(p);
	}

	
	if (bfactor(p) == -2) {
		if( bfactor(p->left) > 0  ) {
			p->left = rotateleft(p->left);
		}
		return rotateright(p);
	}
	
	return p; 


void print_tree(node* root) {

    if(root->left != NULL) {
        print_tree(root->left);
    }

    if(root->right != NULL) {
        print_tree(root->right);
    }

    printf("%d ", root->data);
}

bool is_binary_search_tree(node *root) {
   
    bool is_left_bin_search = true;
    bool is_right_bin_search = true;

    if(root->left != NULL) {
        if(root->left->data > root->data) {
            return false;
        }
        is_left_bin_search = is_binary_search_tree(root->left);
    }

    if(root->right != NULL) {
        if(root->right->data <= root->data) {
            return false;
        }
        is_right_bin_search = is_binary_search_tree(root->right);
    }

    return is_left_bin_search && is_right_bin_search;
}

bool is_avl_tree(node* root) {
	if(is_binary_search_tree(root) == false) {
		return false;
	}

	// теперь мы уверены, что это дерево является BST bin search tree

	fixheight(root); // пересчитываем его высоту

	
	if (bfactor(root) >= 2 || bfactor(root) <= -2) {

		return false;
	}

	return true;
}

int main(){
    node* mynode = create_node(10);
    mynode->left = create_node(5);
    mynode->left->left = create_node(3);
    mynode->right = create_node(15);
    mynode->left->left->left = create_node(1);
    
    mynode->height = 4;
    mynode->left->height = 3;
    mynode->left->left->height = 2;
    mynode->right->height = 1;
    mynode->left->left->left->height = 1;


	printf("Is it a AVL tree: %d\n", is_avl_tree(mynode));
	
	print_tree(mynode);

    node* root = balance(mynode);

	puts("\nBalanced");

	print_tree(root);
	printf("\nIs it a AVL tree: %d\n", is_avl_tree(root));

	return 0;

}
