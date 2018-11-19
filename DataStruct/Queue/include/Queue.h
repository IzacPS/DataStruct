#ifndef QUEUEE_H_
#define QUEUEE_H_

#ifndef Q_TYPE
#define Q_TYPE int
#endif

struct Q_node
{
	Q_TYPE data;
	struct Q_node* next;
	struct Q_node* prev;
};

struct Queue
{
	int size;
	struct Q_node* head;
	struct Q_node* tail;
};


void Q_Init(struct Queue* Q);
void Q_pushFront(struct Queue * Q, Q_TYPE data);
void Q_pushBack(struct Queue * Q, Q_TYPE data);
Q_TYPE Q_popFront(struct Queue * Q);
Q_TYPE Q_popBack(struct Queue * Q);
int Q_size(struct Queue* Q);
unsigned char Q_isEmpty(struct Queue* Q);
Q_TYPE Q_front(struct Queue* Q);
Q_TYPE Q_back(struct Queue* Q);
void Q_Destroy(struct Queue* Q);

#endif
