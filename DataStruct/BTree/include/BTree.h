#ifndef _BTREE_H_
#define _BTREE_H_

struct node
{
	int key;
	struct node* child[2];
};

struct node** BTree_Init();
int BTree_Add(struct node** root, int key);
struct node* BTree_Search(struct node ** root, int key);
void BTree_PrintOrdem(struct node** root);
void BTree_PrintPosOrdem(struct node** root);
void BTree_PrintPreOrdem(struct node** root);
int BTree_Remove(struct node** root, int key);
void BTree_RemoveEvenKey(struct node ** root);
struct node* BTree_SmallKey(struct node** root);
static struct node* Btree_NewNode(int key);
void BTree_Free(struct node** root);
void BTree_FreeNode(struct node** root);
static struct node * BTree_SearchOddKey(struct node ** root);
static struct node * BTree_SearchEvenKey(struct node ** root);
static struct node * BTree_SearchMaxKey(struct node ** root);

#endif
