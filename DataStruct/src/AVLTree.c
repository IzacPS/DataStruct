#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "../Core/DSDefs.h"
#include "../include/AVLTree.h"

void AVLTree_Init(struct AVLTree* AVL, unsigned int key_size)
{
	AVL->root = malloc(sizeof(struct AVL_node*));
	assert(AVL->root);
	(*AVL->root) = NULL;
	AVL->key_size = key_size;
}

int AVLTree_Add(struct AVLTree* AVL, void* key)
{
	return AVLTree_AddRecursive(AVL->root, key, AVL->key_size);
}

static int AVLTree_AddRecursive(struct AVL_node** root, void* key, unsigned int key_size)
{
	int res;

	assert(root);

	if (!(*root)) {
		(*root) = AVLTree_NewNode(key, key_size);
		return 1;
	}
	struct AVL_node* current = (*root);
	if (key < current->key)
	{
		if ((res = AVLTree_AddRecursive(&(current->child[left]), key, key_size)) == 1)
		{
			if (AVLTree_BalanceFactor(current) >= 2)
			{
				if (key < (*root)->child[left]->key)
					LL(root);
				else
					RR(root);
			}
		}
	}
	else
	{
		if (key > current->key)
		{
			if ((res = AVLTree_AddRecursive(&(current->child[right]), key, key_size)) == 1)
			{
				if (AVLTree_BalanceFactor(current) >= 2)
				{
					if ((*root)->child[right]->key < key)
						RR(root);
					else
						RL(root);
				}
			}
		}
		else
		{
			return 0;
		}
	}

	current->height = MAX(NodeHeight(current->child[left]), NodeHeight(current->child[right])) + 1;

	return res;
}

int AVLTree_Remove(struct AVLTree* AVL, void* key)
{
	return AVLTree_RemoveRecursive(AVL->root, key);
}

int AVLTree_RemoveRecursive(struct AVL_node** root, void* key)
{
	if (!(*root))
		return 0;

	int res;

	if (key < (*root)->key)
	{
		if ((res = AVLTree_RemoveRecursive(&(*root)->child[left], key)) == 1)
		{
			if (AVLTree_BalanceFactor(*root) >= 2)
			{
				if (NodeHeight((*root)->child[right]->child[left]) <= NodeHeight((*root)->child[right]->child[right]))
					RR(root);
				else
					RL(root);
			}
		}
	}
	else if (key > (*root)->key)
	{
		if ((res = AVLTree_RemoveRecursive(&(*root)->child[right], key)) == 1)
		{
			if (AVLTree_BalanceFactor(*root) >= 2)
			{
				if (NodeHeight((*root)->child[left]->child[right]) <= NodeHeight((*root)->child[left]->child[left]))
					LL(root);
				else
					LR(root);
			}
		}
	}
	else
	{
		if (!(*root)->child[left] || !(*root)->child[right])
		{
			struct AVL_node* oldNode = (*root);
			*root = (!(*root)->child[left]) ? (*root)->child[left] : (*root)->child[right];
			free(oldNode);
		}
		else
		{
			struct AVL_node* n = AVLTree_SearchMinNode((*root)->child[right]);
			(*root)->key = n->key;
			AVLTree_RemoveRecursive(&(*root)->child[right], (*root)->key);
			if (AVLTree_BalanceFactor(*root) >= 2)
			{
				if (NodeHeight((*root)->child[left]->child[right]) <= NodeHeight((*root)->child[left]->child[left]))
					LL(root);
				else
					LR(root);
			}
		}
		if (*root)
			(*root)->height = MAX(NodeHeight((*root)->child[left]), NodeHeight((*root)->child[right])) + 1;
		return 1;
	}
	(*root)->height = MAX(NodeHeight((*root)->child[left]), NodeHeight((*root)->child[right])) + 1;

	return res;
}

static void RR(struct AVL_node** root)
{
	struct AVL_node* n = (*root)->child[right];
	(*root)->child[right] = n->child[left];
	n->child[left] = (*root);
	(*root)->height = MAX(NodeHeight((*root)->child[left]), NodeHeight((*root)->child[right])) + 1;
	n->height = MAX(NodeHeight(n->child[right]), (*root)->height) + 1;
	(*root) = n;
}

static void LL(struct AVL_node** root)
{
	struct AVL_node* n = (*root)->child[left];
	(*root)->child[left] = n->child[right];
	n->child[right] = (*root);
	(*root)->height = MAX( NodeHeight((*root)->child[left]) , NodeHeight((*root)->child[right])) + 1;
	n->height = MAX(NodeHeight(n->child[left]), (*root)->height) + 1;
	(*root) = n;
}

static void RL(struct AVL_node** root)
{
	LL(&((*root)->child[right]));
	RR(root);
}

static void LR(struct AVL_node** root)
{
	RR(&((*root)->child[left]));
	LL(root);
}

static struct AVL_node* AVLTree_NewNode(void* key, unsigned int key_size)
{
	struct AVL_node* n = malloc(sizeof(struct AVL_node));
	assert(n != NULL);

	n->key = malloc(key_size);
	memcpy(n->key, key, key_size);
	n->child[left] = NULL;
	n->child[right] = NULL;
	n->height = 0;

	return n;
}

struct AVL_node* AVLTree_SearchMinNode(struct AVL_node* root)
{
	struct AVL_node* n = root;

	while (n->child[left])
		n = n->child[left];

	return n;
}

static int AVLTree_BalanceFactor(struct AVL_node* root) 
{
	return labs(NodeHeight(root->child[left]) - NodeHeight(root->child[right]));
}

void AVLTree_Destroy(struct AVLTree* AVL)
{
	if (!AVL->root)
		return;

	AVLTree_FreeNode(*AVL->root);
	free(AVL->root);
}

static void AVLTree_FreeNode(struct AVL_node* root)
{
	if (!root)
		return;

	AVLTree_FreeNode(root->child[left]);
	AVLTree_FreeNode(root->child[right]);
	free(root->key);
	free(root);
	root = NULL;
}

