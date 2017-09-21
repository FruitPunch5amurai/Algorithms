#include "simple_logger.h"
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
PriorityQueue_t* CreatePriorityQueue(Uint32 size,size_t dataSize)
{
	PriorityQueue_t* q;
	q = (PriorityQueue_t*)malloc(sizeof(PriorityQueue_t));
	memset(q, 0, sizeof(PriorityQueue_t));
	if (q != NULL)
	{
		q->elements = (void*)malloc(size * sizeof(element_t));
		memset(q->elements, 0, sizeof(element_t)*size);
		if (q->elements != NULL)
		{
			q->size = size;
			q->numberOfElements = 0;
			q->elementSize = dataSize;
			return q;
		}
		slog("Error making Priority Queue elements");
		return;
	}
	slog("Error making Priority Queue");
	return;
}
void FreePriorityQueue(PriorityQueue_t* q)
{
	if (q != NULL)
	{
		if (q->elements != NULL)
			free(q->elements);
		else
		{
			slog("Priority Queue Elements is NULL");
			return;
		}
	}
	else {
		slog("Priority Queue passed is NULL");
		return;
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
			q->size = q->size * 2;
			if (q->elements != NULL)
			{
				q->elements = (element_t*)realloc(q->elements, (q->size) * sizeof(element_t));
				memset(&q->elements[q->numberOfElements], 0, sizeof(element_t)*(q->size / 2));
			}
			else
			{
				slog("Error Resizing Priority Queue during Enqueue");
				return;
			}
		}
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
element_t PriorityQueue_Dequeue(PriorityQueue_t* q)
{
	element_t e;
	e = q->elements[0];
	memmove(&q->elements[0], &q->elements[1], sizeof(element_t)*(q->numberOfElements));
	q->numberOfElements--;
	memset(&q->elements[q->numberOfElements], 0, sizeof(element_t)*q->size - (q->numberOfElements));
	return e;
}
char* PriorityQueue_AsArray(PriorityQueue_t* q)
{
	int i, numOfElements;
	char* ptr;
	char* data;
	numOfElements = q->numberOfElements;
	data = malloc(q->elementSize * q->numberOfElements);
	memset(data, 0, q->elementSize*q->numberOfElements);
	ptr = data;
	for (i = 0;i < numOfElements;i++)
	{
		memcpy(ptr, q->elements[i].data, q->elementSize);
		ptr = ptr + q->elementSize;
	}
	return data;
}