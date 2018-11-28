#include "../include/Stack.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void stk_Init(struct stk* stk, unsigned int data_size)
{
	stk->top = malloc(sizeof(struct stk_node*));
	assert(stk->top);
	stk->size = 0;
	stk->data_size = data_size;
	(*stk->top) = NULL;

}

//struct stk_node* stk_NewNode(void* data)
//{
//	struct stk_node* n = malloc(sizeof(struct stk_node));
//	assert(n);
//	n->data = malloc();
//	n->next = NULL;
//	n->prev = NULL;
//
//	return n;
//}

void stk_push(struct stk* stk, void* data)
{
	struct stk_node* an = malloc(stk->data_size);
	assert(an);
	if (!*(stk->top))
	{
		*(stk->top) = memcpy(an, data, stk->data_size);
		
		stk->size++;
	}
	else
	{
		
		an->next = (*stk->top);
		(*stk->top)->prev = an;
		(*stk->top) = an;
		stk->size++;
	}
}

void* stk_pop(struct stk* stk)
{
	void* ret;
	if (!*stk->top)
		return (void*)0;
	else
	{
		struct stk_node* an = (*stk->top);
		(*stk->top) = (*stk->top)->next;
		
		if((*stk->top))
			(*stk->top)->prev = NULL;
		
		ret = an->data;
		free(an);
	}
	stk->size--;
	return ret;
}

void* stk_top(struct stk* stk)
{
	if (stk_isEmpty(stk))
		return (void*)0;
	else
		return (*stk->top)->data;
}

unsigned char stk_isEmpty(struct stk* stk)
{
	return (stk->size == 0);
}

void stk_destroy(struct stk* stk)
{
	if (!stk_isEmpty(stk))
		return;

	while (!stk_isEmpty(stk))
		stk_pop(stk);
	
	free(stk->top);
}