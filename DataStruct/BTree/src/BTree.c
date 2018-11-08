#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "../include/BTree.h"

struct node** BTree_Init()
{
	struct node** root= malloc(sizeof(struct node*));
	assert(root != NULL);
	*root = NULL;

	return root;
}

void BTree_Add(struct node ** root, int key)
{
	if (!root) return;
	
	if (!(*root))
	{
		struct node* node = Btree_NewNode();
		(*root) = node;
		(*root)->key = key;
	}
	else
	{
		if (key < (*root)->key) 
		{
			BTree_Add(&((*root)->left), key);
		}
		else
		{
			BTree_Add(&((*root)->right), key);
		}
	}
}

struct node* BTree_Search(struct node ** root, int key)
{
	if (!root) return NULL;

	if ((*root)->key == key)
		return (*root);
	else
	{
		if ((*root)->key > key) 
		{
			return BTree_Search(&((*root)->left), key);
		}
		else
		{
			return BTree_Search(&((*root)->right), key);
		}
	}

}

void BTree_PrintOrdem(struct node ** root)
{
	if (!root) return;

	if (*root)
	{
		BTree_PrintOrdem(&((*root)->left));
		printf("%d\n", (*root)->key);
		BTree_PrintOrdem(&((*root)->right));
	}
}

void BTree_PrintPreOrdem(struct node ** root)
{
	if (!root) return;

	if (*root)
	{
		printf("%d\n", (*root)->key);
		BTree_PrintPreOrdem(&((*root)->left));
		BTree_PrintPreOrdem(&((*root)->right));
	}
}


void BTree_PrintPosOrdem(struct node ** root)
{
	if (!root) return;

	if (*root)
	{
		BTree_PrintPosOrdem(&((*root)->left));
		BTree_PrintPosOrdem(&((*root)->right));
		printf("%d\n", (*root)->key);
	}
}


void BTree_Remove(struct node ** root, int key)
{
	if (!root) return;

	if (!(root)) return;

	if ((*root)->key == key)
	{
		struct node* n = (*root);
		(*root) = BTree_SmallKey(&(n->right));
		(*root)->right = n->right;
		free(n);
	}
	else if ((*root)->key < key)
		BTree_Remove(&(*root)->left, key);
	else
		BTree_Remove(&(*root)->right, key);
}

struct node * BTree_SmallKey(struct node ** root)
{
	if (!root) return NULL;

	struct node* no = (*root);

	while(no->left)
		no = no->left;

	return no;
}

struct node * Btree_NewNode()
{
	struct node* n = malloc(sizeof(struct node));
	assert(n != NULL);
	n->key = 0;
	n->left = NULL;
	n->right = NULL;
	return n;
}

void BTree_Free(struct node ** root)
{
	if (!root) return;

	if ((*root))
	{
		BTree_Free(&(*root)->left);
		BTree_Free(&(*root)->right);
		free(*root);
	}
}



