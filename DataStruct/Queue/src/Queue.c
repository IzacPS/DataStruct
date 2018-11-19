#include <stdio.h>
#include <stdlib.h.>
#include <assert.h>
#include "..\include\Queue.h"

void Q_Init(struct Queue * Q)
{
	Q->head = NULL;
	Q->tail = NULL;
	Q->size = 0;
}

struct Q_node* Q_NewNode(Q_TYPE data)
{
	struct Q_node* nn = malloc(sizeof(struct Q_node));
	assert(nn);

	nn->next = NULL;
	nn->prev = NULL;
	nn->data = data;
	
	return nn;
}

void Q_pushFront(struct Queue * Q, Q_TYPE data)
{
	if (!Q->head)
	{
		Q->head = Q_NewNode(data);
		Q->tail = Q->head;
		Q->size++;
	}
	else
	{
		struct Q_node* an = Q_NewNode(data);
		an->next = Q->head;
		an->next->prev = an;
		Q->head = an;
		Q->size++;
	}
}

void Q_pushBack(struct Queue * Q, Q_TYPE data)
{
	if (!Q->tail)
	{
		Q->tail = Q_NewNode(data);
		Q->head = Q->tail;
		Q->size++;
	}
	else
	{
		struct Q_node* an = Q_NewNode(data);
		an->prev = Q->tail;
		an->prev->next = an;
		Q->tail = an;
		Q->size++;
	}
}

Q_TYPE Q_popFront(struct Queue * Q)
{
	struct Q_node* an = malloc(sizeof(struct Q_node));
	struct Q_node* af;
	if (!Q_isEmpty(Q)) 
	{
		*an = *(Q->head);
		af = Q->head;
		Q->head = Q->head->next;
		
		if (!Q->head)
			Q->tail = NULL;
		
		free(af);
		Q->size--;
	}
	return an->data;
}

Q_TYPE Q_popBack(struct Queue * Q)
{
	struct Q_node* an = malloc(sizeof(struct Q_node));
	struct Q_node* af;
	if (!Q_isEmpty(Q))
	{
		*an = *(Q->tail);
		af = Q->tail;
		Q->tail = Q->tail->prev;
		
		if (!Q->tail)
			Q->head = NULL;
		
		free(af);
		Q->size--;
	}
	return an->data;
}


int Q_size(struct Queue * Q)
{
	return Q->size;
}

inline unsigned char Q_isEmpty(struct Queue * Q)
{
	return Q->size == 0;
}

Q_TYPE Q_front(struct Queue * Q)
{
	return Q->head->data;
}

Q_TYPE Q_back(struct Queue * Q)
{
	return Q->tail->data;
}

void Q_Destroy(struct Queue* Q)
{
	while (Q_popBack(Q));
	Q->size = 0;
}
