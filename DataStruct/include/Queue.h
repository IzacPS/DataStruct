#ifndef QUEUEE_H_
#define QUEUEE_H_

struct Q_node
{
	void* data;
	struct Q_node* next;
	struct Q_node* prev;
};

struct Queue
{
	unsigned int size;
	unsigned int data_size;
	struct Q_node* head;
	struct Q_node* tail;
};


void Q_Init(struct Queue* Q, unsigned int data_size);
void Q_pushFront(struct Queue * Q, void* data);
void Q_pushBack(struct Queue * Q, void* data);
void* Q_popFront(struct Queue * Q);
void* Q_popBack(struct Queue * Q);
int Q_size(struct Queue* Q);
unsigned char Q_isEmpty(struct Queue* Q);
void* Q_front(struct Queue* Q);
void* Q_back(struct Queue* Q);
void Q_Destroy(struct Queue* Q);


#endif
