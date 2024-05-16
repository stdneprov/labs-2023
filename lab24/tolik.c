void Do(Node *tree, int k, int sum) {
    if (tree == NULL) {
        return;
    }
    if (tree->left != NULL && tree->right != NULL) {
        if (*tree->key.symb == '+') {
            if (tree->left->type == NUM && tree->right->type == NUM) {
                k += 1;
            }
            if (tree->left->type == NUM) {
                //k += 1;
                sum += tree->left->key.num;
            }
            if (tree->right->type == NUM) {
                //k += 1;
                sum += tree->right->key.num;
            } 
            if (*tree->left->key.symb == '+') {
                if (tree->right->type == NUM) {
                    k += 1;
                }
                Do(tree->left, k, sum);
            }
            if (*tree->right->key.symb == '+') {
                if (tree->left->type == NUM) {
                    k += 1;
                }
                Do(tree->right, k, sum);
            }
            if (tree->left->type == NUM && tree->right->type == NUM) {
                tree->type = NUM;
                tree->key.symb = NULL;
                tree->key.num = tree->left->key.num + tree->right->key.num;
                tree->right = NULL;
                tree->left = NULL;
                k -= 1;
                return;
            }
        }
    }
}