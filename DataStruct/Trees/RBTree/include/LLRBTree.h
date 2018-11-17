#ifndef _BRTREE_H_
#define _BRTREE_H_
#include "../../../Core/DSDefs.h"

#define TYPE int

enum Color
{
	RED,
	BLACK
};

enum Orientation
{
	NORMAL,
	REVERSE
};

struct LLRB_node
{	
	TYPE key;
	unsigned char Color;
	struct LLRB_node* child[2];
};

struct LLRB_node** LLRB_Init();
static inline struct LLRB_node* LLRB_NewNode(TYPE key);
static struct LLRB_node* LLRB_SearchNode(struct LLRB_node* root, TYPE key);
void LLRB_Add(struct LLRB_node** root, TYPE key, enum Orientation orientation);
static struct LLRB_node* LLRB_AddNode(struct LLRB_node* root, TYPE key);
static struct LLRB_node* LLRB_AddNodeReverse(struct LLRB_node* root, TYPE key);
void LLRB_Remove(struct LLRB_node** root, TYPE key);
static struct LLRB_node* LLRB_RemoveNode(struct LLRB_node* root, TYPE key);
static inline struct LLRB_node* LLRB_RR(struct LLRB_node* root);
static inline struct LLRB_node* LLRB_LL(struct LLRB_node * root);
static struct LLRB_node* LLRB_LR(struct LLRB_node * root);
static struct LLRB_node* LLRB_RL(struct LLRB_node * root);
static int LLRB_Depth(struct LLRB_node** root);
static inline void LLRB_ChangeColor(struct LLRB_node* root);
static struct LLRB_node* LLRB_MoveRedNodeToLeft(struct LLRB_node* root);
static struct LLRB_node* LLRB_MoveRedNodeToRight(struct LLRB_node* root);
static struct LLRB_node* LLRB_ToBalance(struct LLRB_node* root);
static struct LLRB_node* LLRB_MinValueAtRightSubTree(struct LLRB_node* root);
static void LLRB_FreeNode(struct LLRB_node* root);
void LLRB_DestroyTree(struct LLRB_node** root);
static struct LLRB_node* LLRB_RemoveMinValue(struct LLRB_node* root);
void LLRB_Print(struct LLRB_node** root, enum Path path);
static void LLRB_PrintPreOrdem(struct LLRB_node** root, int h);
static void LLRB_PrintOrdem(struct LLRB_node** root, int h);
static void LLRB_PrintPosOrdem(struct LLRB_node** root, int h);
int LLRB_NumNodes(struct LLRB_node** root);
int LLRB_Height(struct LLRB_node** root);
unsigned char LLRB_areSimilarTrees(struct LLRB_node ** root1, struct LLRB_node ** root2);
static unsigned char LLRB_areSimilarTreesRecursion(struct LLRB_node ** root1, struct LLRB_node ** root2);
unsigned char LLRB_areEqualTrees(struct LLRB_node ** root1, struct LLRB_node ** root2);
static unsigned char LLRB_areEqualTreesRecursion(struct LLRB_node ** root1, struct LLRB_node ** root2);

#endif
