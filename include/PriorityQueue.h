#ifndef __PRIORITYQUEUE_H__
#define __PRIORITYQUEUE_H__

#include <SDL.h>


typedef struct element
{
	void *data;
	Uint32 priority;

}element_t;
typedef struct PriorityQueue
{
	element_t *elements;
	Uint32 numberOfElements;
	Uint32 size;

}PriorityQueue_t;

PriorityQueue_t* CreatePriorityQueue(Uint32 size);
element_t PriorityQueue_Dequeue(PriorityQueue_t* q);
void PriorityQueue_Enqueue(PriorityQueue_t* q, void *data, Uint32 priority);
/*
Linked list implementation of a queue
*/
/*
typedef struct node
{
void **data;
struct node* next;
Uint32 priority;
}node_t;

typedef struct PriorityQueue
{
node_t* head;
node_t* tail;
Uint32 numOfElements;

}PriorityQueue_t;

PriorityQueue_t* CreatePriorityQueue();
void PriorityQueue_Enqueue(PriorityQueue_t* q, void* data, Uint32 priority);
node_t* PriorityQueue_Dequeue(PriorityQueue_t* q);
void* PriorityQueue_RetrieveData(node_t* n);
*/


/*
typedef struct
{
	void **data;
	Uint32 *priorities;
	Uint32 numberOfElements;
	Uint32 size;

}PriorityQueue;
PriorityQueue* CreatePriorityQueue(Uint32 size);
void  Insert(PriorityQueue *q, void* data, int priority);
void* SearchFirst(PriorityQueue *q);
void* SearchLast(PriorityQueue *q);
void* Search(PriorityQueue *q, void* data);
*/

#endif