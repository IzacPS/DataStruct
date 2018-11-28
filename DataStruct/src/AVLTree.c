#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "../Core/DSDefs.h"
#include "../include/AVLTree.h"

struct AVL_node ** AVLTree_Init()
{
	struct AVL_node** root = malloc(sizeof(struct AVL_node*));
	assert(root != NULL);
	(*root) = NULL;
	return root;
}

int AVLTree_Add(struct AVL_node** root, KEY key)
{
	int res;

	assert(root != NULL);

	if (!(*root)) {
		*root = AVLTree_NewNode(key);
		return 1;
	}
	struct AVL_node* current = *root;
	if (key < current->key)
	{
		if ((res = AVLTree_Add(&(current->child[left]), key)) == 1)
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
			if ((res = AVLTree_Add(&(current->child[right]), key)) == 1)
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

int AVLTree_Remove(struct AVL_node** root, KEY key)
{
	if (!(*root))
		return 0;

	int res;

	if (key < (*root)->key)
	{
		if ((res = AVLTree_Remove(&(*root)->child[left], key)) == 1)
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
		if ((res = AVLTree_Remove(&(*root)->child[right], key)) == 1)
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
			AVLTree_Remove(&(*root)->child[right], (*root)->key);
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

void AVLTree_RemoveOddNode(struct AVL_node** root)
{
	if (!root || !(*root))
		return;

	AVLTree_RemoveOddNode(&(*root)->child[left]);
	AVLTree_RemoveOddNode(&(*root)->child[right]);

	if((*root)->key % 2 == 0){
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
			AVLTree_Remove(&(*root)->child[right], (*root)->key);
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
	}
	(*root)->height = MAX(NodeHeight((*root)->child[left]), NodeHeight((*root)->child[right])) + 1;
}

unsigned char AVLTree_IsSearchTree(struct AVL_node** root)
{
	assert(root != NULL);

	if (!*root)
		return 0;
	
	const unsigned char i = AVLTree_IsSearchTree(&(*root)->child[left]) & AVLTree_IsSearchTree(&(*root)->child[right]);
	
	if (!(*root)->child[left] && !(*root)->child[right])
		return 0;

	if ((*root)->child[left]->key > (*root)->key || (*root)->child[right]->key < (*root)->key)
		return 0;
	else
		return 1 & i;	
}

void RR(struct AVL_node** root)
{
	struct AVL_node* n = (*root)->child[right];
	(*root)->child[right] = n->child[left];
	n->child[left] = (*root);
	(*root)->height = MAX(NodeHeight((*root)->child[left]), NodeHeight((*root)->child[right])) + 1;
	n->height = MAX(NodeHeight(n->child[right]), (*root)->height) + 1;
	(*root) = n;
}

void LL(struct AVL_node ** root)
{
	struct AVL_node* n = (*root)->child[left];
	(*root)->child[left] = n->child[right];
	n->child[right] = (*root);
	(*root)->height = MAX( NodeHeight((*root)->child[left]) , NodeHeight((*root)->child[right])) + 1;
	n->height = MAX(NodeHeight(n->child[left]), (*root)->height) + 1;
	(*root) = n;
}

void RL(struct AVL_node ** root)
{
	LL(&((*root)->child[right]));
	RR(root);
}

void LR(struct AVL_node ** root)
{
	RR(&((*root)->child[left]));
	LL(root);
}

struct AVL_node* AVLTree_NewNode(KEY key)
{
	struct AVL_node* n = malloc(sizeof(struct AVL_node));
	assert(n != NULL);

	n->key = key;
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

void AVLTree_Destroy(struct AVL_node** root)
{
	if (!root)
		return;

	AVLTree_FreeNode(*root);
	free(root);
}

static void AVLTree_FreeNode(struct AVL_node* root)
{
	if (!root)
		return;

	AVLTree_FreeNode(root->child[left]);
	AVLTree_FreeNode(root->child[right]);
	free(root);
	root = NULL;
}

int AVLTree_Height(struct AVL_node** root)
{
	if (!(*root))
		return 0;

	int LeftHeight = AVLTree_Height(&(*root)->child[left]);
	int RightHeight = AVLTree_Height(&(*root)->child[right]);

	return (LeftHeight > RightHeight) ? LeftHeight + 1 : RightHeight + 1;
}

int AVLTree_NumNodes(struct AVL_node** root)
{
	if (!(*root))
		return 0;

	int LeftHeight = AVLTree_Height(&(*root)->child[left]);
	int RightHeight = AVLTree_Height(&(*root)->child[right]);

	return LeftHeight + RightHeight + 1;
}

struct AVL_node* AVLTree_MaxKey(struct AVL_node** root)
{
	if (!*root)
		return NULL;

	struct AVL_node* LeftNode = AVLTree_MaxKey(&(*root)->child[left]);
	struct AVL_node* RightNode = AVLTree_MaxKey(&(*root)->child[right]);

	if (LeftNode->key == RightNode->key)
		return LeftNode;
	return (LeftNode->key > RightNode->key) ? LeftNode : RightNode;
}

int AVLTree_NumOfLeaves(struct AVL_node** root)
{
	if (!(*root)->child[left] && !(*root)->child[right])
		return 1;

	int QtdLeft = AVLTree_NumOfLeaves(&(*root)->child[left]);
	int QtdRight = AVLTree_NumOfLeaves(&(*root)->child[right]);

	return QtdLeft + QtdRight;
}

