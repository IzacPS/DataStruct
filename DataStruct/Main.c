#include <vld.h>
#include <stdio.h>
#include <stdlib.h>
#include "include/BTree.h"

int main()
{
	struct node** arv = BTree_Init();

	BTree_Add(arv, 10);
	BTree_Add(arv, 6);
	BTree_Add(arv, 7);
	BTree_Add(arv, 20);

	BTree_Print(arv);
	getchar();
	BTree_Free(arv);

	free(arv);
}