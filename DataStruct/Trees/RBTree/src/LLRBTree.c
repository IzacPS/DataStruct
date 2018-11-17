#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "../include/LLRBTree.h"


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
		const unsigned char direction = (key > root->key);

		return LLRB_SearchNode(root->child[direction], key);
	}
}

void LLRB_Add(struct LLRB_node** root, TYPE key, enum Orientation orientation)
{
	assert(root != NULL);

	switch(orientation)
	{
	case NORMAL:
		*root = LLRB_AddNode(*root, key);
		break;
	case REVERSE:
		*root = LLRB_AddNodeReverse(*root, key);
		break;
	default:
		break;
	}

	if (*root)
		(*root)->Color = BLACK;
}

static struct LLRB_node* LLRB_AddNode(struct LLRB_node* root, TYPE key)
{

	if (!root)
	{
		return LLRB_NewNode(key);
	}
	else if(root->key != key)
	{
		const unsigned char direction = (key > root->key);
		
		root->child[direction] = LLRB_AddNode(root->child[direction], key);
	}

	if (IsRed(NodeColor(root->child[right])) && !IsRed(NodeColor(root->child[left])))
		root = LLRB_LL(root);

	if (IsRed(NodeColor(root->child[left])) && IsRed(NodeColor(root->child[left]->child[left])))
		root = LLRB_RR(root);

	if (IsRed(NodeColor(root->child[left])) && IsRed(NodeColor(root->child[right])))
		LLRB_ChangeColor(root);

	return root;
}

static struct LLRB_node* LLRB_AddNodeReverse(struct LLRB_node* root, TYPE key)
{

	if (!root)
	{
		return LLRB_NewNode(key);
	}
	else if (root->key != key)
	{
		const unsigned char direction = (key < root->key);

		root->child[direction] = LLRB_AddNode(root->child[direction], key);
	}

	if (IsRed(NodeColor(root->child[right])) && !IsRed(NodeColor(root->child[left])))
		root = LLRB_LL(root);

	if (IsRed(NodeColor(root->child[left])) && IsRed(NodeColor(root->child[left]->child[left])))
		root = LLRB_RR(root);

	if (IsRed(NodeColor(root->child[left])) && IsRed(NodeColor(root->child[right])))
		LLRB_ChangeColor(root);

	return root;
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
		case PREORDER:
			LLRB_PrintPreOrdem(&(*root), 0);
			break;
		case INORDER:
			LLRB_PrintOrdem(&(*root), 0);
			break;
		case POSTORDER:
			LLRB_PrintPosOrdem(&(*root), 0);
			break;
		default:
			break;
		}
	}
}

static void LLRB_PrintPreOrdem(struct LLRB_node** root, int h)
{
	if ((*root))
	{
		printf("[%d %s h:%d] ", (*root)->key, ((*root)->Color) ? "black" : "red", h);
		LLRB_PrintPreOrdem(&(*root)->child[left], h+1);
		LLRB_PrintPreOrdem(&(*root)->child[right], h+1);
	}
}

static void LLRB_PrintOrdem(struct LLRB_node** root, int h)
{
	if ((*root))
	{
		LLRB_PrintOrdem(&(*root)->child[left], h+1);
		printf("[%d %s h:%d] ", (*root)->key, ((*root)->Color) ? "black" : "red", h);
		LLRB_PrintOrdem(&(*root)->child[right], h+1);
	}
}

static void LLRB_PrintPosOrdem(struct LLRB_node** root, int h)
{
	if ((*root))
	{
		LLRB_PrintPosOrdem(&(*root)->child[left], h+1);
		LLRB_PrintPosOrdem(&(*root)->child[right] , h+1);
		printf("[%d %s h:%d] ", (*root)->key, ((*root)->Color) ? "black" : "red", h);
	}
}

int LLRB_NumNodes(struct LLRB_node ** root)
{
	if (!(*root))
		return 0;

	int LeftHeight = LLRB_NumNodes(&(*root)->child[left]);
	int RightHeight = LLRB_NumNodes(&(*root)->child[right]);

	return LeftHeight + RightHeight + 1;
}

int LLRB_Height(struct LLRB_node ** root)
{
	if (!(*root))
		return 1;

	int LeftHeight = LLRB_Height(&(*root)->child[left]);
	int RightHeight = LLRB_Height(&(*root)->child[right]);

	int Adicional = ((*root)->Color == BLACK) ? 1 : 0;

	return (LeftHeight > RightHeight) ? LeftHeight + Adicional : RightHeight + Adicional;
}

int LLRB_NumOfNonLeafNodes(struct LLRB_node ** root)
{
	if (!(*root)->child[left] && !(*root)->child[right])
		return 0;

	int LeftHeight = LLRB_NumNodes(&(*root)->child[left]);
	int RightHeight = LLRB_NumNodes(&(*root)->child[right]);

	return LeftHeight + RightHeight + 1;
}

void LLRB_MirrorTree(struct LLRB_node** NormalTreeRoot, struct LLRB_node** TreeReverseRoot)
{
	if (NormalTreeRoot)
	{
		LLRB_MirrorTree(&(*NormalTreeRoot)->child[left], TreeReverseRoot);
		LLRB_Add(TreeReverseRoot, (*NormalTreeRoot)->key, REVERSE);
		LLRB_MirrorTree(&(*NormalTreeRoot)->child[right], TreeReverseRoot);
	}
}

unsigned char LLRB_areSimilarTrees(struct LLRB_node** root1, struct LLRB_node** root2)
{
	assert(root1 || root2);

	if (!*root1 && !*root2)
		return 1;
	else
		return LLRB_areSimilarTreesRecursion(root1, root2);
}

static unsigned char LLRB_areSimilarTreesRecursion(struct LLRB_node** root1, struct LLRB_node** root2)
{
	unsigned char leftResult = 1, rightResult = 1, result = 1;

	if (*root1 && *root2)
	{
		leftResult = LLRB_areSimilarTreesRecursion(&(*root1)->child[left], &(*root2)->child[left]);
		rightResult = LLRB_areSimilarTreesRecursion(&(*root1)->child[right], &(*root2)->child[right]);
		
		if ((*root1)->child[left] && (*root2)->child[left] && (*root1)->child[right] && (*root2)->child[right])
			result = 1 && leftResult && rightResult;
		else if (!(*root1)->child[left] && !(*root2)->child[left] && (*root1)->child[right] && (*root2)->child[right])
			result = 1 && leftResult && rightResult;
		else if ((*root1)->child[left] && (*root2)->child[left] && !(*root1)->child[right] && !(*root2)->child[right])
			result = 1 && leftResult && rightResult;
		else if (!(*root1)->child[left] && !(*root2)->child[left] && !(*root1)->child[right] && !(*root2)->child[right])
			result = 1 && leftResult && rightResult;
		else
			result = 0 && leftResult && rightResult;

		printf("result:%d, leftResult:%d, rightResult%d, key%d\n", result, leftResult, rightResult, (*root1)->key);
	}
	return result;
}

unsigned char LLRB_areEqualTrees(struct LLRB_node** root1, struct LLRB_node** root2)
{
	assert(root1 || root2);

	if (!*root1 && !*root2)
		return 1;
	else
		return LLRB_areEqualTreesRecursion(root1, root2);
}

static unsigned char LLRB_areEqualTreesRecursion(struct LLRB_node** root1, struct LLRB_node** root2)
{
	unsigned char leftResult = 1, rightResult = 1, result = 1;

	if (*root1 && *root2)
	{
		leftResult = LLRB_areEqualTreesRecursion(&(*root1)->child[left], &(*root2)->child[left]);
		rightResult = LLRB_areEqualTreesRecursion(&(*root1)->child[right], &(*root2)->child[right]);

		if ((*root1)->key == (*root2)->key)
			result = 1 && leftResult && rightResult;
		else
			result = 0 && leftResult && rightResult;

		printf("result:%d, leftResult:%d, rightResult%d, key%d\n", result, leftResult, rightResult, (*root1)->key);
	}
	return result;
}

