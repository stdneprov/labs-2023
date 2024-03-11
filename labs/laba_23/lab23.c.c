#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<stdbool.h>


// структура для представления узлов дерева
// typedef ......... node - это нужно для того, чтобы не писать далее каждый раз struct node (то есть мы создали свой псевдоним)
typedef struct node 
{
	int data; // данные самого узла, само хранимое число
	unsigned char height; // unsigned - беззнаковый char - 1 байт число. от 0 до 256
	// высота узла, то есть сколько под ним максимально узлов, да + 1 за него самого (по умолчанию у всех 1)
	// 2 потомка
	struct node* left; 
	struct node* right;
} node;


// создание нового узла
node* create_node(int data) {
	// динамическое выделение памяти для узла
    struct node* node = (struct node*)malloc(sizeof(struct node)); // у малока в скобках число - количество необходимых байт
	// скобка перед малоком - преобразование к нужному типу (int), (float), (char*), .... и т.д.
	// "преобразуй эти байты к данному типу" и дай их адрес этому указателю

	// данные вписали
    node->data = data;

	// детей нет
    node->left = NULL;
    node->right = NULL;
    
	// по умолчанию высота 1
	node->height = 1;

    return node; // вернули адрес этой новой памяти
}

//
unsigned char height(node* p) // беззнаковый 
{
	// если вы мне дали указатель в никуда - я верну ноль, так как иначе сломаюсь
	if(p != NULL) {
		return p->height; // если бы p был NULL, это действие вызвало бы исключение во время исполнения программы
	} else {
		return 0;
	}
	// то же самое, но тернарный оператор (для краткости)
	// return p != NULL ? p->height : 0;
}

int bfactor(node* p) {
	// возвращает разницу между высотами левого и правого поддерева
	return height(p->right) - height(p->left);
	// имеем в виду, что мы не стали проверять p на NULL, хотя это может привести к ошибке
}

// функция пересчёта высоты для узла после поворота дерева
void fixheight(node* p) {
	// получение высот двух детей
	unsigned char hl = height(p->left);
	unsigned char hr = height(p->right);

	// у каждого узла выше высота больше на 1, чем от его поддерева
	p->height = (hl > hr ? hl : hr) + 1;
}

// функции вращения
node* rotateright(node* p) // правый поворот вокруг p
{
	// условно мы - это p

	node* q = p->left; // запоминаем адрес текущего левого
	p->left = q->right; // теперь делаем нашим левым правого от нашего левого
	q->right = p; // наш бывший левый поднялся и сделал нас справа от себя

	// и теперь пересчитываем высоты только для этих двоих: нас и бывшего левого
	fixheight(p);
	fixheight(q);

	// и возращаем наружу новый корень данного дерева, то есть нашего бывшего левого
	// возвращаем наружу его адрес
	return q;
}
node* rotateleft(node* q) // левый поворот вокруг q
{
	node* p = q->right;

	q->right = p->left;
	p->left = q;
	
	fixheight(q);
	fixheight(p);
	
	return p;
}


// самая главная функция, которая будет вызываться из main. Балансирует дерево
// балансировка узла p
node* balance(node* p) {
	// р - корень некоторого дерева \ поддерева
	fixheight(p); // пересчитываем его высоту

	// если разница дала 2, значит, у нас перевес в правое поддерево
	if (bfactor(p) == 2) {
		if( bfactor(p->right) < 0 ) {
			p->right = rotateright(p->right);
		}
		return rotateleft(p);
	}

	// перевес в левое поддерево
	if (bfactor(p) == -2) {
		if( bfactor(p->left) > 0  ) {
			p->left = rotateleft(p->left);
		}
		return rotateright(p);
	}
	
	return p; // балансировка не нужна
}

// node* insert(node* p, int k) // вставка ключа k в дерево с корнем p
// {
// 	if( !p ){
//         return create_node(k);
//     }
// 	if( k<p->data )
// 		p->left = insert(p->left,k);
// 	else
// 		p->right = insert(p->right,k);
// 	return balance(p);
// }

void print_tree(node* root) {
    // root - указатель на корневой узел дерева

    // слева что-то есть? Если да - идём туда
    if(root->left != NULL) {
        print_tree(root->left);
    }

    if(root->right != NULL) {
        print_tree(root->right);
    }

    printf("%d ", root->data);
}

// проверка, является ли БДП
// для работы данной функции высоты не имеют значения
bool is_binary_search_tree(node *root) {
    // true;
    // false;
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

	// если разница дала 2, значит, у нас перевес в правое поддерево
	if (bfactor(root) >= 2 || bfactor(root) <= -2) {
		// значит не сбалансированное БДП. Для АВЛ допустимо 0, 1, -1. Поэтому оно не является АВЛ
		
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


// node* findmin(node* p) // поиск узла с минимальным ключом в дереве p 
// {
// 	return p->left?findmin(p->left):p;
// }

// node* removemin(node* p) // удаление узла с минимальным ключом из дерева p
// {
// 	if( p->left==0 )
// 		return p->right;
// 	p->left = removemin(p->left);
// 	return balance(p);
// }

// node* remove(node* p, int k) // удаление ключа k из дерева p
// {
// 	if( !p ) return 0;
// 	if( k < p->data )
// 		p->left = remove(p->left,k);
// 	else if( k > p->data )
// 		p->right = remove(p->right,k);	
// 	else //  k == p->data 
// 	{
// 		node* q = p->left;
// 		node* r = p->right;
// 		delete p;
// 		if( !r ) return q;
// 		node* min = findmin(r);
// 		min->right = removemin(r);
// 		min->left = q;
// 		return balance(min);
// 	}
// 	return balance(p);
// }