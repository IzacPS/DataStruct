#include <vld.h>
#include <stdio.h>
#include <stdlib.h>
#include "Trees/RBTree/include/LLRBTree.h"

int main()
{
	struct LLRB_node** root1 = LLRB_Init();
	struct LLRB_node** root2 = LLRB_Init();
	//int i, N = 10, val[10] ={10,20,30,40,50,15,18,25,38,28};
//int i, N = 10, val[10] ={10,20,30,40,50,15,18,25,33,28};
//int i, N = 8, val[8] ={10,85,15,70,20,60,30,50};
//int i, N = 8, val[8] ={8,10,15,18,14,20,16,22};
//int i, N = 4, val[4] ={5,30,20,10};

//int i, N = 7, val[7] ={10,15,20,30,70,85,50};
//int i, N = 7, val[7] ={85,10,30,70,15,20,50};
	//int i, N = 4, val[4] = {20,30,5,10};
	int i, N = 10, M=8, val[10] = { 0,1,2,3,4,5,6,7,8,9 }, val2[8] = {34, 4, 5, 7, 3, 2, 7, 4};
	int j = 0;
	for (i = 0; i < N; i++) {
		/*
		if(insere_ArvLLRB(raiz,val[i]))
			printf("Insercao: %d -> OK\n",val[i]);
		else
			printf("Insercao: %d -> ERRO\n",val[i]);
		*/
		//printf("Insercao: %d -> OK\n",val[i]);
		LLRB_Add(root1, val[i], NORMAL);
		LLRB_Add(root2, val[i]/*val[(j < M) ? j++ : j]*/, NORMAL);
		//emOrdem_ArvLLRB(raiz,0);
		//printf("\n\n==========================\n\n");
	}

	if (LLRB_areEqualTrees(root1, root2))
		printf("Similares");
	
	//LLRB_Print(root1, INORDER);
	//LLRB_Print(root2, INORDER);

	LLRB_DestroyTree(root1);
	LLRB_DestroyTree(root2);
}
