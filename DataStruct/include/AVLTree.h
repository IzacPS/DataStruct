#ifndef _AVL_TREE_H_
#define _AVL_TREE_H_



struct AVL_node
{
	void* key;
	int height;
	struct AVL_node* child[2];
};

struct AVLTree 
{
	unsigned int key_size;
	struct AVL_node** root;
};

void AVLTree_Init(struct AVLTree* AVL, unsigned int key_size);
int AVLTree_Add(struct AVLTree* AVL, void* key);
static int AVLTree_AddRecursive(struct AVL_node ** root, void * key, unsigned int key_size);
int AVLTree_Remove(struct AVLTree* AVL, void* key);
int AVLTree_RemoveRecursive(struct AVL_node** root, void* key);
static void RR(struct AVL_node** root);
static void LL(struct AVL_node** root);
static void LR(struct AVL_node** root);
static void RL(struct AVL_node** root);
static void AVLTree_FreeNode(struct AVL_node* root);
static int AVLTree_BalanceFactor(struct AVL_node* root);
struct AVL_node* AVLTree_SearchMinNode(struct AVL_node* root);
void AVLTree_Destroy(struct AVLTree* AVL);
static inline struct AVL_node* AVLTree_NewNode(void* key, unsigned int ke_size);

#endif
