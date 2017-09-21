#include "simple_logger.h"
#include "PriorityQueue.h"
/**
@brief Create Priority Queue 
*/
PQueue* CreatePQueue(Uint32 size, size_t datasize)
{
	PQueue* p;
	p = malloc(sizeof(PQueue));
	if (p != NULL & size != 0)
	{
		p->list = List_Create(size, datasize);
		return p;
	}
	slog("Could not initialize PQueue");
}
/**
@brief Free Priority Queue
*/
void FreePQueue(PQueue* q)
{
	if (q != NULL)
	{
		List_Free(q->list);
		free(q);
	}
}
/**
@brief Enqueue data with priority 
*/
void PQueue_Enqueue(PQueue* q, void *data, Uint32 priority)
{
	Uint32 half;
	int left;
	int right;
	if (q != NULL)
		if(q->list != NULL)
		{ 
			{
			//Priority using binary search
			left = 0;
			right = q->list->numElements - 1;

			half = left + (right - left) / 2;
			while (right >= left)
			{
				if (priority < q->list->list[half].priority)
				{
					left = half + 1;
				}
				else
				{
					right = half - 1;
				}
				half = left + (right - left) / 2;
			}
			if (priority >=  q->list->list[half].priority)
			{
				List_Insert(q->list, data, half);
			}
			else
			{
				half++;
				List_Insert(q->list, data, half);
			}
			q->list->list[half].priority = priority;
		}
	}
}
/**
@brief Dequeue from queue
*/
ListElement PQueue_Dequeue(PQueue* q)
{
	ListElement e;
	e = List_Get(q->list, 0);
	q->list = List_Delete(q->list, 0);
	return e;
}
/**
@brief Return Priority as an array
*/
char* PQueue_AsArray(PQueue* q)
{
	return List_AsArray(q->list);
}
