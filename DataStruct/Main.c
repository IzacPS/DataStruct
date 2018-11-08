#include <vld.h>
#include <stdio.h>
#include <stdlib.h>
#include "RBTree/include/LLRBTree.h"

int main()
{
	struct LLRB_node** root = LLRB_Init();
	//int i, N = 10, val[10] ={10,20,30,40,50,15,18,25,38,28};
//int i, N = 10, val[10] ={10,20,30,40,50,15,18,25,33,28};
//int i, N = 8, val[8] ={10,85,15,70,20,60,30,50};
//int i, N = 8, val[8] ={8,10,15,18,14,20,16,22};
//int i, N = 4, val[4] ={5,30,20,10};

//int i, N = 7, val[7] ={10,15,20,30,70,85,50};
//int i, N = 7, val[7] ={85,10,30,70,15,20,50};
	int i, N = 10, val[10] = {0,1,2,3,4,5,6,7,8,9};
	//int i, N = 10, val[10] ={10,15,10,20,30,70,70,85,50,50};

	for (i = 0; i < N; i++) {
		/*
		if(insere_ArvLLRB(raiz,val[i]))
			printf("Insercao: %d -> OK\n",val[i]);
		else
			printf("Insercao: %d -> ERRO\n",val[i]);
		*/
		//printf("Insercao: %d -> OK\n",val[i]);
		LLRB_Add(root, val[i]);
		//emOrdem_ArvLLRB(raiz,0);
		//printf("\n\n==========================\n\n");
	}

	LLRB_Print(root, POS_ORDEM);
	

	LLRB_DestroyTree(root);
}
