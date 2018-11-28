#ifndef _STACK_H_
#define _STACK_H_

struct stk_node
{
	void* data;
	struct stk_node* next;
	struct stk_node* prev;
};

struct stk
{
	struct stk_node** top;
	unsigned int size;
	unsigned int data_size;
};

void stk_Init(struct stk* stk, unsigned int data_size);
void stk_push(struct stk* stk, void* data);
void* stk_pop(struct stk* stk);
void* stk_top(struct stk* stk);
unsigned char stk_isEmpty(struct stk * stk);
void stk_destroy(struct stk* stk);
unsigned char stk_isEmpty(struct stk* stk);

#endif
