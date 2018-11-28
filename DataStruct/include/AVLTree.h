#ifndef _AVL_TREE_H_
#define _AVL_TREE_H_

#ifndef KEY
#define KEY int
#endif


struct AVL_node
{
	int key;
	int height;
	struct AVL_node* child[2];
};

struct AVL_node** AVLTree_Init();
int AVLTree_Add(struct AVL_node** root, KEY key);
int AVLTree_Remove(struct AVL_node** root, KEY key);
void RR(struct AVL_node** root);
void LL(struct AVL_node** root);
void LR(struct AVL_node** root);
void RL(struct AVL_node** root);
static void AVLTree_FreeNode(struct AVL_node* root);
static int AVLTree_BalanceFactor(struct AVL_node * root);
struct AVL_node* AVLTree_SearchMinNode(struct AVL_node* root);
void AVLTree_Destroy(struct AVL_node** root);
static inline struct AVL_node* AVLTree_NewNode(KEY key);
int AVLTree_Height(struct AVL_node** root);
int AVLTree_NumNodes(struct AVL_node ** root);
int AVLTree_NumOfLeaves(struct AVL_node** root);

#endif
