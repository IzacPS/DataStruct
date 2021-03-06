#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "test.h"
#include "../Core/DSDefs.h"
#include "../include/LLRBTree.h"
#include "../include/Stack.h"
#include "../include/Queue.h"

int NumOfNonLeafNodes(struct LLRB_node ** root)
{
	if (!(*root)->child[left] && !(*root)->child[right])
		return 0;

	int LeftHeight = LLRB_NumNodes(&(*root)->child[left]);
	int RightHeight = LLRB_NumNodes(&(*root)->child[right]);

	return LeftHeight + RightHeight + 1;
}

void MirrorTree(struct LLRB_node** NormalTreeRoot, struct LLRB_node** TreeReverseRoot)
{
	if (NormalTreeRoot)
	{
		MirrorTree(&(*NormalTreeRoot)->child[left], TreeReverseRoot);
		LLRB_Add(TreeReverseRoot, (*NormalTreeRoot)->key, REVERSE);
		MirrorTree(&(*NormalTreeRoot)->child[right], TreeReverseRoot);
	}
}

unsigned char areSimilarTrees(struct LLRB_node** root1, struct LLRB_node** root2)
{
	assert(root1 || root2);

	if (!*root1 && !*root2)
		return 1;
	else
		return areSimilarTreesRecursion(root1, root2);
}

static unsigned char areSimilarTreesRecursion(struct LLRB_node** root1, struct LLRB_node** root2)
{
	unsigned char leftResult = 1, rightResult = 1, result = 1;

	if (*root1 && *root2)
	{
		leftResult = areSimilarTreesRecursion(&(*root1)->child[left], &(*root2)->child[left]);
		rightResult = areSimilarTreesRecursion(&(*root1)->child[right], &(*root2)->child[right]);

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

unsigned char areEqualTrees(struct LLRB_node** root1, struct LLRB_node** root2)
{
	assert(root1 || root2);

	if (!*root1 && !*root2)
		return 1;
	else
		return areEqualTreesRecursion(root1, root2);
}

static unsigned char areEqualTreesRecursion(struct LLRB_node** root1, struct LLRB_node** root2)
{
	unsigned char leftResult = 1, rightResult = 1, result = 1;

	if (*root1 && *root2)
	{
		leftResult = areEqualTreesRecursion(&(*root1)->child[left], &(*root2)->child[left]);
		rightResult = areEqualTreesRecursion(&(*root1)->child[right], &(*root2)->child[right]);

		if ((*root1)->key == (*root2)->key)
			result = 1 && leftResult && rightResult;
		else
			result = 0 && leftResult && rightResult;
	}
	return result;
}

int MinValueInterative(struct LLRB_node** root, int index)
{
	struct stk stk;
	stk_Init(&stk, sizeof(struct LLRB_node*));

	int MinValue = INT_MAX;

	stk_push(&stk, (*root));
	struct LLRB_node* an;

	int count = 0;

	while (!stk_isEmpty(&stk))
	{
		an = stk_top(&stk);
		stk_pop(&stk);

		if (count == index)
			return an->key;
		count++;

		if (an->child[right])
			stk_push(&stk, an->child[right]);
		if (an->child[left])
			stk_push(&stk, an->child[left]);
	}
	stk_destroy(&stk);

	return MinValue;
}

int SmallerOrEqual(struct LLRB_node** root, int value)
{
	struct stk stk;
	stk_Init(&stk, sizeof(struct LLRB_node*));

	int MinValue = INT_MAX;

	stk_push(&stk, (*root));
	struct LLRB_node* an;

	while (!stk_isEmpty(&stk))
	{
		an = stk_top(&stk);
		stk_pop(&stk);

		if (an->key <= value)
			MinValue = an->key;
		else
			return MinValue;

		if (an->child[right])
			stk_push(&stk, an->child[right]);
		if (an->child[left])
			stk_push(&stk, an->child[left]);
	}
	stk_destroy(&stk);

	return MinValue;
}

int SearchValueInterative(struct LLRB_node** root, int value)
{
	struct stk stk;
	stk_Init(&stk, sizeof(struct LLRB_node*));

	stk_push(&stk, (*root));
	struct LLRB_node* an;

	while (!stk_isEmpty(&stk))
	{
		an = stk_top(&stk);
		stk_pop(&stk);

		if (an->key == value)
			return 1;

		if (an->child[right])
			stk_push(&stk, an->child[right]);
		if (an->child[left])
			stk_push(&stk, an->child[left]);
	}
	stk_destroy(&stk);

	return 0;
}

int SearchNegativeValueInterative(struct LLRB_node** root)
{
	struct stk stk;
	stk_Init(&stk, sizeof(struct LLRB_node*));

	stk_push(&stk, (*root));
	struct LLRB_node* an;

	while (!stk_isEmpty(&stk))
	{
		an = stk_top(&stk);
		stk_pop(&stk);

		if (an->key < 0)
			return 1;

		if (an->child[right])
			stk_push(&stk, an->child[right]);
		if (an->child[left])
			stk_push(&stk, an->child[left]);
	}
	stk_destroy(&stk);

	return 0;
}

unsigned char IsSearchTree(struct LLRB_node** root)
{
	assert(root != NULL);

	if (!*root)
		return 0;

	const unsigned char i = IsSearchTree(&(*root)->child[left]) && IsSearchTree(&(*root)->child[right]);

	if (!(*root)->child[left] && !(*root)->child[right])
		return 0;

	if ((*root)->child[left]->key > (*root)->key || (*root)->child[right]->key < (*root)->key)
		return 0;
	else
		return 1 && i;
}

int HeightIterative(struct LLRB_node** root)
{

	struct Queue Q;
	Q_Init(&Q, sizeof(struct LLRB_node*));

	int Height = 0;
	int nodeCount = 0;
	unsigned char flag;
	const unsigned char one = 1;
	const unsigned char zero = 0;

	Q_pushBack(&Q, (*root));


	while (1)
	{
		nodeCount = Q_size(&Q);

		if (nodeCount == 0)
			return Height;

		//if (flag)
		Height++;

		flag = 0;

		while (nodeCount > 0)
		{
			struct LLRB_node* an = Q_back(&Q);
			Q_popBack(&Q);

			//flag |= (an->Color == BLACK) ? one : zero;

			if (an->child[left])
				Q_pushBack(&Q, an->child[left]);
			if (an->child[right])
				Q_pushBack(&Q, an->child[right]);
			nodeCount--;
		}
	}
}

void PrintPathsRootToLeaves(struct LLRB_node* root)
{
	struct Queue Q[2];
	struct LLRB_node an;
	unsigned char q = 0;

	Q_Init(&Q[q], sizeof(struct LLRB_node));
	Q_Init(&Q[!q], sizeof(struct LLRB_node));

	Q_pushBack(&Q[q], root);

	while (!Q_isEmpty(&Q[q]))
	{
		an = *(struct LLRB_node*)Q_back(&Q[q]);

		if (an.child[left])
		{
			Q_pushBack(&Q[q], (an.child[left]));
		}
		else if (an.child[right])
		{
			Q_pushBack(&Q[q], (an.child[right]));
		}
		else
		{
			struct LLRB_node aux;

			while (!Q_isEmpty(&Q[q]))
			{
				aux = *(struct LLRB_node*)Q_front(&Q[q]);
				Q_pushBack(&Q[!q], Q_front(&Q[q]));
				Q_popFront(&Q[q]);

				printf("[%d %s] ", aux.key, (aux.Color) ? "black" : "red");
			}
			printf("\n");
			q = !q;

			struct LLRB_node* aa;
			
			do
			{
				an = *(struct LLRB_node*)Q_back(&Q[q]);
				Q_popBack(&Q[q]);
				if (Q_isEmpty(&Q[q]))
					break;

				aa = (struct LLRB_node*)Q_back(&Q[q]);

				if (aa->child[left] && an.key == aa->child[left]->key)
					aa->child[left] = NULL;
				if (aa->child[right] && an.key == aa->child[right]->key)
					aa->child[right] = NULL;

			} while (!aa->child[left] && !aa->child[right]);

		}
	}


}

void PrintAllLevelsTree(struct LLRB_node *root) 
{
	
	struct Queue Q[2];
	unsigned char s = 0;
	struct LLRB_node an;

	Q_Init(&Q[s], sizeof(struct LLRB_node));
	Q_Init(&Q[!s], sizeof(struct LLRB_node));

	Q_pushBack(&Q[s], root);

	while (!Q_isEmpty(&Q[s]))
	{
		while (!Q_isEmpty(&Q[s]))
		{
			an = *(struct LLRB_node*)Q_front(&Q[s]);
			Q_popFront(&Q[s]);
			printf("[%d %s] ", an.key, (an.Color) ? "black" : "red");
			if (an.child[left])
				Q_pushBack(&Q[!s], an.child[left]);
			if (an.child[right])
				Q_pushBack(&Q[!s], an.child[right]);
		}
		printf("\n");
		s = !s;
	}

	Q_Destroy(&Q[!s]);
	
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

static struct node* BTree_SearchOddKey(struct node** root)
{
	if (!*root)
		return NULL;
	if ((*root)->key % 2 != 0)
		return (*root);

	struct node* LeftNode = BTree_SearchOddKey(&(*root)->child[left]);
	struct node* RightNode = BTree_SearchEvenKey(&(*root)->child[right]);

	if (LeftNode && RightNode)
		return LeftNode;
	if (LeftNode && !RightNode)
		return LeftNode;
	if (!LeftNode && RightNode)
		return RightNode;
	if (!LeftNode && !RightNode)
		return NULL;
}

static struct node* BTree_SearchEvenKey(struct node** root)
{
	if (!*root)
		return NULL;
	if ((*root)->key % 2 == 0)
		return (*root);

	struct node* LeftNode = BTree_SearchOddKey(&(*root)->child[left]);
	struct node* RightNode = BTree_SearchEvenKey(&(*root)->child[right]);

	if (LeftNode && RightNode)
		return LeftNode;
	if (LeftNode && !RightNode)
		return LeftNode;
	if (!LeftNode && RightNode)
		return RightNode;
	if (!LeftNode && !RightNode)
		return NULL;
}

static struct node* BTree_SearchMaxKey(struct node** root)
{
	if (!*root)
		return NULL;

	struct node* LeftNode = BTree_SearchOddKey(&(*root)->child[left]);
	struct node* RightNode = BTree_SearchEvenKey(&(*root)->child[right]);

	if (!LeftNode && RightNode)
		return RightNode;
	if (LeftNode && !RightNode)
		return LeftNode;
	if (!LeftNode && !RightNode)
		return NULL;
	return (LeftNode->key > RightNode->key) ? LeftNode : RightNode;
}


/*
void BTree_SearchKey(struct node** root, enum Parity parity)
{
	assert(root != NULL);

	switch (parity)
	{
		case Even:
			break;
		case Odd:
			break;
		default :
			break;
	}
}*/


int BTree_MinValueInterative(struct node** root)
{
	struct stk stk;
	stk_Init(&stk, sizeof(struct LLRB_node*));

	stk_push(&stk, (*root));
	struct node* an;
	int MinValue = INT_MAX;

	while (!stk_isEmpty(&stk))
	{
		an = stk_top(&stk);
		stk_pop(&stk);

		if (an->key < MinValue)
			MinValue = an->key;

		if (an->child[right])
			stk_push(&stk, an->child[right]);
		if (an->child[left])
			stk_push(&stk, an->child[left]);
	}
	stk_destroy(&stk);

	return MinValue;
}

void BTree_RemoveEvenKey(struct node** root)
{
	if (!root)
		return;
	if (!*root)
		return;

	BTree_RemoveEvenKey(&(*root)->child[left]);
	BTree_RemoveEvenKey(&(*root)->child[right]);

	if ((*root)->key % 2 == 0)
		(*root) = BTree_RemoveCurrent((*root));
}static struct node* BTree_SearchOddKey(struct node** root)
{
	if (!*root)
		return NULL;
	if ((*root)->key % 2 != 0)
		return (*root);

	struct node* LeftNode = BTree_SearchOddKey(&(*root)->child[left]);
	struct node* RightNode = BTree_SearchEvenKey(&(*root)->child[right]);

	if (LeftNode && RightNode)
		return LeftNode;
	if (LeftNode && !RightNode)
		return LeftNode;
	if (!LeftNode && RightNode)
		return RightNode;
	if (!LeftNode && !RightNode)
		return NULL;
}

static struct node* BTree_SearchEvenKey(struct node** root)
{
	if (!*root)
		return NULL;
	if ((*root)->key % 2 == 0)
		return (*root);

	struct node* LeftNode = BTree_SearchOddKey(&(*root)->child[left]);
	struct node* RightNode = BTree_SearchEvenKey(&(*root)->child[right]);

	if (LeftNode && RightNode)
		return LeftNode;
	if (LeftNode && !RightNode)
		return LeftNode;
	if (!LeftNode && RightNode)
		return RightNode;
	if (!LeftNode && !RightNode)
		return NULL;
}

static struct node* BTree_SearchMaxKey(struct node** root)
{
	if (!*root)
		return NULL;

	struct node* LeftNode = BTree_SearchOddKey(&(*root)->child[left]);
	struct node* RightNode = BTree_SearchEvenKey(&(*root)->child[right]);

	if (!LeftNode && RightNode)
		return RightNode;
	if (LeftNode && !RightNode)
		return LeftNode;
	if (!LeftNode && !RightNode)
		return NULL;
	return (LeftNode->key > RightNode->key) ? LeftNode : RightNode;
}


/*
void BTree_SearchKey(struct node** root, enum Parity parity)
{
	assert(root != NULL);

	switch (parity)
	{
		case Even:
			break;
		case Odd:
			break;
		default :
			break;
	}
}*/


int BTree_MinValueInterative(struct node** root)
{
	struct stk stk;
	stk_Init(&stk, sizeof(struct LLRB_node*));

	stk_push(&stk, (*root));
	struct node* an;
	int MinValue = INT_MAX;

	while (!stk_isEmpty(&stk))
	{
		an = stk_top(&stk);
		stk_pop(&stk);

		if (an->key < MinValue)
			MinValue = an->key;

		if (an->child[right])
			stk_push(&stk, an->child[right]);
		if (an->child[left])
			stk_push(&stk, an->child[left]);
	}
	stk_destroy(&stk);

	return MinValue;
}

void BTree_RemoveEvenKey(struct node** root)
{
	if (!root)
		return;
	if (!*root)
		return;

	BTree_RemoveEvenKey(&(*root)->child[left]);
	BTree_RemoveEvenKey(&(*root)->child[right]);

	if ((*root)->key % 2 == 0)
		(*root) = BTree_RemoveCurrent((*root));
}

void AVLTree_RemoveOddNode(struct AVL_node** root)
{
	if (!root || !(*root))
		return;

	AVLTree_RemoveOddNode(&(*root)->child[left]);
	AVLTree_RemoveOddNode(&(*root)->child[right]);

	if ((*root)->key % 2 == 0) {
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
