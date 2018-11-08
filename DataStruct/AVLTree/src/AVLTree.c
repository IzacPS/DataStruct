#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "..\include\AVLTree.h"

struct AVL_node ** AVLTree_Init()
{
	struct AVL_node** root = malloc(sizeof(struct AVL_node*));
	assert(root == NULL);
	(*root) = NULL;
	return root;
}

struct AVL_node * RR(struct AVL_node ** root)
{
	struct AVL_node* n = (*root)->left;
	(*root)->left = n->right;
	n->right = (*root);
	return n;
}

struct AVL_node * LL(struct AVL_node ** root)
{
	struct AVL_node* n = (*root)->right;
	(*root)->right = n->left;
	n->left = (*root);
	return n;
}

struct AVL_node * LR(struct AVL_node ** root)
{
	(*root)->left = LL(&((*root)->left));
	return RR(&(*root));
}

struct AVL_node * RL(struct AVL_node ** root)
{
	(*root)->right = RR(&((*root)->right));
	return LL(&(*root));
}


