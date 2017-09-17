#include "PriorityQueue.h"

/*
Linked list implementation of a queue

PriorityQueue_t* CreatePriorityQueue()
{
	PriorityQueue_t *q;
	q = (PriorityQueue_t*)malloc(sizeof(PriorityQueue_t));
	q->head = NULL;
	q->tail = NULL;
	q->numOfElements = 0;
	return q;
}

void PriorityQueue_Enqueue(PriorityQueue_t* q, void* data, Uint32 priority)
{
	node_t* n;
	node_t* temp;
	n = (node_t*)malloc(sizeof(node_t*));
	n->next = NULL;

	n->data = data;
	n->priority = priority;
	if (q->tail != NULL)
	{
		temp = q->tail;
		q->tail = n;
		temp->next = n;
	}
	else
	{
		q->head = n;
		q->tail = n;
	}
}
void* PriorityQueue_RetrieveData(node_t* n)
{
	return n->data;
}
node_t* PriorityQueue_Dequeue(PriorityQueue_t* q)
{
	node_t *n;
	if (q->head != NULL)
	{
		n = q->head;
		q->head = n->next;
		if (q->head == NULL)
			q->tail = NULL;
		return n;

	}
}
*/

/*
List implementation of a priority queue
*/
PriorityQueue_t* CreatePriorityQueue(Uint32 size)
{
	PriorityQueue_t* q;
	q = (PriorityQueue_t*)malloc(sizeof(PriorityQueue_t));
	memset(q, 0, sizeof(PriorityQueue_t));
	q->elements = (void*)malloc(size * sizeof(element_t));
	memset(q->elements, 0, sizeof(element_t)*size);
	q->size = size;
	q->numberOfElements = 0;
	return q;
}
void FreePriorityQueue(PriorityQueue_t* q)
{
	if (q->elements)
	{
		free(q->elements);
	}
	free(q);
}
void PriorityQueue_Enqueue(PriorityQueue_t* q, void *data, Uint32 priority)
{
	Uint32 half;
	int left;
	int right;

	if (q != NULL)
	{		//Resize
		if (q->numberOfElements >= q->size)
		{
			q->elements = (element_t*)realloc(q->elements, (q->size*3) * sizeof(element_t));
			memset(&q->elements[q->numberOfElements],0,sizeof(element_t)*q->size);
			q->size = q->size * 2;
		}
		if (q->numberOfElements < q->size)
		{
			//Priority using binary search
			left = 0;
			right = q->numberOfElements - 1;

			half = left + (right - left) / 2;
			while (right >= left)
			{
				if (priority < q->elements[half].priority)
				{
					left = half + 1;
				}
				else
				{
					right = half - 1;
				}
				half = left + (right - left) / 2;
			}
			if (priority > q->elements[half].priority)
			{
				memmove(&q->elements[half + 1], &q->elements[half], sizeof(element_t)*(q->numberOfElements - half));
			}
			else
			{
				half++;
				memmove(&q->elements[half + 1], &q->elements[half], sizeof(element_t)*(q->numberOfElements - half));
			}
			q->elements[half].data = data;
			q->elements[half].priority = priority;
			q->numberOfElements++;
		}
	}
}
element_t PriorityQueue_Dequeue(PriorityQueue_t* q)
{
	element_t e;
	e = q->elements[0];
	memmove(&q->elements[0], &q->elements[1], sizeof(element_t)*(q->numberOfElements));
	q->numberOfElements--;
	memset(&q->elements[q->numberOfElements], 0, sizeof(element_t)*q->size - (q->numberOfElements));
	return e;
}







/*
PriorityQueue * CreatePriorityQueue(Uint32 size)
{
	PriorityQueue * p;
	p = (PriorityQueue*)malloc(sizeof(PriorityQueue));

	p->data = (void**)malloc(size * sizeof(*(p->data)));
	p->priorities = malloc(size * sizeof(int));
	p->size = size;
	p->numberOfElements = 0;
	return p;
}

void Insert(PriorityQueue * q, void* data, int priority)
{
	size_t halfLen;
	int temp = NULL;
	void *temp2 = NULL;
	char test;
	int test2;

	if(q != NULL)
	{
		if (q->numberOfElements >= q->size)
		{
			q->size = q->size * 2;
			q->data = (void *)realloc(q->data, q->size * sizeof(q->data));
		}
		q->data[q->numberOfElements] = (void*)data;
		q->priorities[q->numberOfElements] = priority;
		

		q->numberOfElements++;
		halfLen = q->numberOfElements / 2;
	}
	while (q->priorities[halfLen] >= priority)
	{
		halfLen = halfLen / 2;
	} 
	while (halfLen < q->numberOfElements-1)
	{
		temp = q->priorities[halfLen];
		temp2 = q->data[halfLen];
		
		q->priorities[halfLen] = q->priorities[q->numberOfElements-1];
		q->priorities[q->numberOfElements -1] = temp;

		q->data[halfLen] = q->data[q->numberOfElements-1];
		q->data[q->numberOfElements-1] = temp2;

		halfLen++;
	}
	test = q->data[q->numberOfElements-1];
	test2 = q->priorities[q->numberOfElements-1];

	test = q->data[1];
	test2 = q->priorities[1];


	test = q->data[0];
	test2 = q->priorities[0];

	/*
	if (q->numberOfElements + 1 >= q->size)
	{
		q->size = q->size * 2;
		q->data = (void *)realloc(q->data, q->size * sizeof(void *));
	}
	int len = q->numberOfElements + 1;
	int halflen = len / 2;
	char *s = (char *)q->data;
;	while (len > 1 && q->data[halflen]> priority)
	{

	}
}

void * SearchFirst(PriorityQueue * q)
{
	return NULL;
}

void * SearchLast(PriorityQueue * q)
{
	return NULL;
}

void * Search(PriorityQueue * q, void * data)
{
	return NULL;
}
*/