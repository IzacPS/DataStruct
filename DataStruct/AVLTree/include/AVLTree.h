#ifndef _AVL_TREE_H_
#define _AVL_TREE_H_

enum RotationDirection
{
	LEFT = -1,
	BALANCED = 0,
	RIGHT = 1
};

struct AVL_node
{
	int key;
	struct AVL_node* left;
	struct AVL_node* right;
};

struct AVL_node** AVLTree_Init();
void AVLTree_Add(struct AVL_node** root, int key);
void AVLTree_Remove(struct AVL_node** root, int* key);
struct AVL_node* RR(struct AVL_node** root);
struct AVL_node* LL(struct AVL_node** root);
struct AVL_node* LR(struct AVL_node** root);
struct AVL_node* RL(struct AVL_node** root);
int AVL_Height(struct AVL_node** root);

#endif
