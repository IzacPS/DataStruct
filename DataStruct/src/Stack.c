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

static struct stk_node* stk_NewNode(void* data, unsigned int data_size)
{
	struct stk_node* n = malloc(sizeof(struct stk_node));
	assert(n);
	n->data = malloc(data_size);
	assert(n->data);
	memcpy(n->data, data, data_size);
	n->next = NULL;
	n->prev = NULL;

	return n;
}

void stk_push(struct stk* stk, void* data)
{
	struct stk_node* an = stk_NewNode(data, stk->data_size);
	assert(an);
	if (!*(stk->top))
	{
		*(stk->top) = an;
		
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

void stk_pop(struct stk* stk)
{
	if (!*stk->top)
		return;
	else
	{
		struct stk_node* an = (*stk->top);
		(*stk->top) = (*stk->top)->next;
		
		if((*stk->top))
			(*stk->top)->prev = NULL;
		
		free(an->data);
		free(an);
	}
	stk->size--;
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
	if (stk_isEmpty(stk))
		return;

	while (!stk_isEmpty(stk))
		stk_pop(stk);
	
	free(stk->top);
}