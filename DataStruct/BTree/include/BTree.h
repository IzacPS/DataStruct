#ifndef _BTREE_H_
#define _BTREE_H_

struct node
{
	int key;
	struct node* left;
	struct node* right;
};

struct node** BTree_Init();
void BTree_Add(struct node** root, int key);
struct node* BTree_Search(struct node ** root, int key);
//int BTree_QtdElements(struct node** root);
void BTree_PrintOrdem(struct node** root);
void BTree_PrintPosOrdem(struct node** root);
void BTree_PrintPreOrdem(struct node** root);
void BTree_Remove(struct node** root, int key);
struct node* BTree_SmallKey(struct node** root);
struct node* Btree_NewNode();
void BTree_Free(struct node** root);

#endif
