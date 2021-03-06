#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "../Core/DSDefs.h"
#include "../include/BTree.h"
#define STK_TYPE struct node*
#include "../include/Stack.h"

struct node** BTree_Init()
{
	struct node** root= malloc(sizeof(struct node*));
	assert(root != NULL);
	*root = NULL;

	return root;
}

int BTree_Add(struct node ** root, int key)
{
	if (root) return 0;
	
	struct node* node = Btree_NewNode(key);

	if (!(*root))
		*root = node;
	else 
	{
		struct node* current = *root;
		struct node* prev = NULL;
		while (current) 
		{
			prev = current;
			if (key == current->key) 
			{
				free(node);
				return 0;
			}
			current = (key > current->key) ? current->child[right] : current->child[left];
		}
		current = (key > current->key) ? current->child[right] : current->child[left];
	}
	return 1;
}

struct node* BTree_RemoveCurrent(struct node* current)
{
	struct node* n1;
	struct node* n2;
	if (!current->child[left])
	{
		n2 = current->child[right];
		free(current);
		return n2;
	}
	n1 = current;
	n2 = current->child[left];
	while (n2->child[right]) 
	{
		n1 = n2;
		n2 = n2->child[right];
	}

	if (n2 != current)
	{
		n1->child[right] = n2->child[left];
		n2->child[left] = current->child[left];
	}
	n2->child[right] = current->child[right];
	free(current);
	return n2;
}

int BTree_Remove(struct node** root, int key)
{
	if (!root)
		return 0;

	struct node* prev = NULL;
	struct node* current = *root;
	while(current)
	{
		if (key == current->key)
		{
			if (current == *root)
				*root = BTree_RemoveCurrent(current);
			else
			{
				if (prev->child[right] = current)
					prev->child[right] = BTree_RemoveCurrent(current);
				else
					prev->child[left] = BTree_RemoveCurrent(current);
			}
			return 1;
		}
		prev = current;
		current = (key > current->key) ? current->child[right] : current->child[left];
	}
	return 0;
}

/*
void BTree_Remove(struct node ** root, int key)
{
	if (!root) return;

	if (!(root)) return;

	if ((*root)->key == key)
	{
		struct node* n = (*root);
		(*root) = BTree_SmallKey(&(n->child[right]));
		(*root)->child[right] = n->child[right];
		free(n);
	}
	else
	{
		const unsigned char direction = ((*root)->key < key);
		BTree_Remove(&(*root)->child[direction], key);
	}
}*/



int BTree_IsEmpty(struct node** root)
{
	return (!root || !(*root));
}

//struct node* BTree_Search(struct node ** root, int key)
//{
//	if (!root) return NULL;
//
//	if ((*root)->key == key)
//		return (*root);
//	else
//	{
//		//const unsigned char direction = ((*root)->key < key);
//		//return BTree_Search(&((*root)->child[direction]), key);
//	}
//
//}

void BTree_PrintOrdem(struct node ** root)
{
	if (!root) return;

	if (*root)
	{
		BTree_PrintOrdem(&((*root)->child[left]));
		printf("%d\n", (*root)->key);
		BTree_PrintOrdem(&((*root)->child[right]));
	}
}

void BTree_PrintPreOrdem(struct node ** root)
{
	if (!root) return;

	if (*root)
	{
		printf("%d\n", (*root)->key);
		BTree_PrintPreOrdem(&((*root)->child[left]));
		BTree_PrintPreOrdem(&((*root)->child[right]));
	}
}

void BTree_PrintPosOrdem(struct node ** root)
{
	if (!root) return;

	if (*root)
	{
		BTree_PrintPosOrdem(&((*root)->child[left]));
		BTree_PrintPosOrdem(&((*root)->child[right]));
		printf("%d\n", (*root)->key);
	}
}

struct node * BTree_SmallKey(struct node ** root)
{
	if (!root) return NULL;

	struct node* no = (*root);

	while(no->child[left])
		no = no->child[left];

	return no;
}

struct node * Btree_NewNode(int key)
{
	struct node* n = malloc(sizeof(struct node));
	assert(n != NULL);
	n->key = key;
	n->child[left] = NULL;
	n->child[right] = NULL;
	return n;
}

void BTree_Free(struct node ** root)
{
	if (!root)
		return;

	BTree_FreeNode(root);
	free(root);
}

static void BTree_FreeNode(struct node ** root)
{
	if (!root) return;

	if ((*root))
	{
		BTree_FreeNode(&(*root)->child[left]);
		BTree_FreeNode(&(*root)->child[right]);
		free(*root);
		*root = NULL;
	}
}

