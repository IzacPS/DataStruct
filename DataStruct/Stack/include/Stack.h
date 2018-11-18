#ifndef _STACK_H_
#define _STACK_H_

#ifndef STK_TYPE
#define STK_TYPE int
#endif

struct stk_node
{
	STK_TYPE data;
	struct stk_node* next;
	struct stk_node* prev;
};

struct stk
{
	struct stk_node** top;
	unsigned int size;
};

void stk_Init(struct stk* stk);
void stk_push(struct stk* stk, STK_TYPE data);
STK_TYPE stk_pop(struct stk* stk);
STK_TYPE stk_top(struct stk* stk);
unsigned char stk_isEmpty(struct stk * stk);
void stk_destroy(struct stk* stk);
unsigned char stk_isEmpty(struct stk* stk);

#endif
