#ifndef _BRTREE_H_
#define _BRTREE_H_
#include "../../Core/DSDefs.h"

#define TYPE int

enum Color
{
	RED,
	BLACK
};

enum Direction
{
	left,
	right
};

struct LLRB_node
{
	TYPE key;
	struct LLRB_node* child[2];
	unsigned char Color;
};

struct LLRB_node** LLRB_Init();
static inline struct LLRB_node* LLRB_NewNode(TYPE key);
static struct LLRB_node* LLRB_SearchNode(struct LLRB_node* root, TYPE key);
void LLRB_Add(struct LLRB_node** root, TYPE key);
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
static void LLRB_PrintPreOrdem(struct LLRB_node** root);
static void LLRB_PrintOrdem(struct LLRB_node** root);
static void LLRB_PrintPosOrdem(struct LLRB_node** root);


#endif
