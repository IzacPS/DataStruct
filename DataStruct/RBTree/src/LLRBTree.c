#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "..\include\LLRBTree.h"


struct LLRB_node** LLRB_Init()
{
	struct LLRB_node** n = malloc(sizeof(struct LLRB_node*));
	assert(n != NULL);
	*n = NULL;
	return n;
}

static inline struct LLRB_node* LLRB_NewNode(TYPE key)
{
	struct LLRB_node* n = malloc(sizeof(struct LLRB_node));
	assert(n != NULL);
	n->key = key;
	n->child[left] = NULL;
	n->child[right] = NULL;
	n->Color = RED;
	return n;
}

static struct LLRB_node* LLRB_SearchNode(struct LLRB_node* root, TYPE key)
{
	assert(root != NULL);

	if (root->key == key || !root)
	{
		return root;
	}
	else
	{
		const unsigned char direction = (root->key > key);

		return LLRB_SearchNode(root->child[direction], key);
	}
}

void LLRB_Add(struct LLRB_node** root, TYPE key)
{
	assert(root != NULL);

	if (!(*root))
	{
		(*root) = LLRB_NewNode(key);
	}
	else if((*root)->key != key)
	{
		const unsigned char direction = ((*root)->key < key);
		LLRB_Add(&(*root)->child[direction], key);
	}

	if (IsRed(NodeColor((*root)->child[right])) && !IsRed(NodeColor((*root)->child[left])))
		(*root) = LLRB_LL(*root);

	if (IsRed(NodeColor((*root)->child[left])) && IsRed(NodeColor((*root)->child[left]->child[left])))
		(*root) = LLRB_RR(*root);

	if (IsRed(NodeColor((*root)->child[left])) && IsRed(NodeColor((*root)->child[right])))
		LLRB_ChangeColor(*root);

	if ((*root))
		(*root)->Color = BLACK;
}

void LLRB_Remove(struct LLRB_node** root, TYPE key)
{
	assert(root != NULL);

	if (LLRB_SearchNode(*root, key))
		*root = LLRB_RemoveNode(*root, key);
}

static struct LLRB_node* LLRB_RemoveNode(struct LLRB_node* root, TYPE key)
{
	if (key < root->key)
	{
		if (!IsRed(NodeColor(root->child[left])) && !IsRed(NodeColor(root->child[left]->child[left])))
			root = LLRB_MoveRedNodeToLeft(root);
		
		root->child[left] = LLRB_RemoveNode(root->child[left], key);
	}
	else
	{
		if (IsRed(NodeColor(root->child[left])))
			root = LLRB_RR(root);

		if (key == root->key && !(root->child[right]))
		{
			free(root);
			 return NULL;
		}

		if (!IsRed(NodeColor(root->child[right])) && !IsRed(NodeColor(root->child[right]->child[left])))
			root = LLRB_MoveRedNodeToRight(root);

		if (key == root->key)
		{
			struct LLRB_node* n = LLRB_MinValueAtRightSubTree(root->child[right]);
			root->key = n->key;
			root->child[right] = LLRB_RemoveMinValue(root->child[right]);
		}
		else
			root->child[right] = LLRB_RemoveNode(root->child[right], key);
	}
	return LLRB_ToBalance(root);
}

static inline struct LLRB_node* LLRB_RR(struct LLRB_node* root)
{
	struct LLRB_node* n = root->child[left];
	root->child[left] = n->child[right];
	n->child[right] = root;
	n->Color = root->Color;
	root->Color = RED;
	return n;
}

static inline struct LLRB_node* LLRB_LL(struct LLRB_node * root)
{
	struct LLRB_node* n = root->child[right];
	root->child[right] = n->child[left];
	n->child[left] = root;
	n->Color = root->Color;
	root->Color = RED;
	return n;
}

static struct LLRB_node* LLRB_LR(struct LLRB_node * root)
{
	root->child[left] = LLRB_LL(root->child[left]);
	return LLRB_RR(root);
}

static struct LLRB_node* LLRB_RL(struct LLRB_node * root)
{
	root->child[right] = LLRB_RR(root->child[right]);
	return LLRB_LL(root);
}

static int LLRB_Depth(struct LLRB_node** root)
{
	if (!(*root))
		return 0;

	int LeftDepth = LLRB_Depth(&(*root)->child[left]);
	int RightDepth = LLRB_Depth(&(*root)->child[right]);

	return (LeftDepth > RightDepth) ? LeftDepth + 1 : RightDepth + 1;
}

static inline void LLRB_ChangeColor(struct LLRB_node* root)
{
	assert(root != NULL);

	root->Color = !root->Color;

	if (root->child[left])
		root->child[left]->Color = !(root->child[left]->Color);
	if (root->child[right])
		root->child[right]->Color = !(root->child[right]->Color);
}

static struct LLRB_node* LLRB_MoveRedNodeToLeft(struct LLRB_node* root)
{
	LLRB_ChangeColor(root);
	if (IsRed(NodeColor(root->child[right]->child[left]))) {
		root = LLRB_RL(root->child[right]);
		LLRB_ChangeColor(root);
	}
	return root;
}

static struct LLRB_node* LLRB_MoveRedNodeToRight(struct LLRB_node* root)
{
	LLRB_ChangeColor(root);
	if (IsRed(NodeColor(root->child[left]->child[left])))
	{
		root = LLRB_RR(root);
		LLRB_ChangeColor(root);
	}
	return root;
}

static struct LLRB_node* LLRB_ToBalance(struct LLRB_node* root)
{
	if (IsRed(NodeColor(root->child[right])))
		root = LLRB_LL(root);

	if (!root->child[left] && IsRed(NodeColor(root->child[right])) && IsRed(NodeColor(root->child[left]->child[left])))
		root = LLRB_RR(root);

	if (IsRed(NodeColor(root->child[right])) && IsRed(NodeColor(root->child[left])))
		LLRB_ChangeColor(root);

	return root;
}

static struct LLRB_node* LLRB_MinValueAtRightSubTree(struct LLRB_node* root)
{
	struct LLRB_node* n = root;

	while (n->child[left])
		n = n->child[left];

	return n;
}

static void LLRB_FreeNode(struct LLRB_node* root)
{
	if (!root)
		return;
	LLRB_FreeNode(root->child[left]);
	LLRB_FreeNode(root->child[right]);
	free(root);
	root = NULL;
}

void LLRB_DestroyTree(struct LLRB_node** root)
{
	if (!root)
		return;

	LLRB_FreeNode(*root);
	free(root);
}

static struct LLRB_node* LLRB_RemoveMinValue(struct LLRB_node* root)
{
	if (!root->child[left])
	{
		free(root);
		return NULL;
	}
	if (!IsRed(NodeColor(root->child[left])) && !IsRed(NodeColor(root->child[left]->child[left])))
		root = LLRB_MoveRedNodeToLeft(root);

	root->child[left] = LLRB_RemoveMinValue(root->child[left]);
	return LLRB_ToBalance(root);
}

void LLRB_Print(struct LLRB_node** root, enum Path path)
{
	if ((*root))
	{
		switch (path)
		{
		case PRE_ORDEM:
			LLRB_PrintPreOrdem(&(*root));
			break;
		case ORDEM:
			LLRB_PrintOrdem(&(*root));
			break;
		case POS_ORDEM:
			LLRB_PrintPosOrdem(&(*root));
			break;
		default:
			break;
		}
	}
}

static void LLRB_PrintPreOrdem(struct LLRB_node** root)
{
	if ((*root))
	{
		printf("%d ", (*root)->key);
		LLRB_PrintPreOrdem(&(*root)->child[left]);
		LLRB_PrintPreOrdem(&(*root)->child[right]);
	}
}

static void LLRB_PrintOrdem(struct LLRB_node** root)
{
	if ((*root))
	{
		LLRB_PrintOrdem(&(*root)->child[left]);
		printf("%d ", (*root)->key);
		LLRB_PrintOrdem(&(*root)->child[right]);
	}
}

static void LLRB_PrintPosOrdem(struct LLRB_node** root)
{
	if ((*root))
	{
		LLRB_PrintPosOrdem(&(*root)->child[left]);
		LLRB_PrintPosOrdem(&(*root)->child[right]);
		printf("%d ", (*root)->key);
	}
}

