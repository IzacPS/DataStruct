#ifndef TEST_H
#define TEST_H
#include "../include/LLRBTree.h"

int NumOfNonLeafNodes(struct LLRB_node ** root);
void MirrorTree(struct LLRB_node ** NormalTreeRoot , struct LLRB_node ** TreeReverseRoot);
unsigned char areSimilarTrees(struct LLRB_node ** root1, struct LLRB_node ** root2);
static unsigned char areSimilarTreesRecursion(struct LLRB_node ** root1, struct LLRB_node ** root2);
unsigned char areEqualTrees(struct LLRB_node ** root1, struct LLRB_node ** root2);
static unsigned char areEqualTreesRecursion(struct LLRB_node ** root1, struct LLRB_node ** root2);
TYPE MinValueInterative(struct LLRB_node ** root, int index);
void PrintPathsRootToLeaves(struct LLRB_node* root);

void PrintAllLevelsTree(struct LLRB_node * root);

#endif