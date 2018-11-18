#include "../include/Stack.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

void stk_Init(struct stk* stk)
{
	stk->top = malloc(sizeof(struct stk_node*));
	assert(stk->top);
	stk->size = 0;
	(*stk->top) = NULL;

}

struct stk_node* stk_NewNode(STK_TYPE data)
{
	struct stk_node* n = malloc(sizeof(struct stk_node));
	assert(n);
	n->data = data;
	n->next = NULL;
	n->prev = NULL;

	return n;
}

void stk_push(struct stk* stk, STK_TYPE data)
{
	if (!*(stk->top))
	{
		*(stk->top) = stk_NewNode(data);
		stk->size++;
	}
	else
	{
		struct stk_node* nn = stk_NewNode(data);
		nn->next = (*stk->top);
		(*stk->top)->prev = nn;
		(*stk->top) = nn;
		stk->size++;
	}
}

STK_TYPE stk_pop(struct stk* stk)
{
	STK_TYPE ret;
	if (!*stk->top)
		return (STK_TYPE)0;
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

STK_TYPE stk_top(struct stk* stk)
{
	if (stk_isEmpty(stk))
		return (STK_TYPE)0;
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