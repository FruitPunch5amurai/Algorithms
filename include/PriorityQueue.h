#ifndef __PRIORITYQUEUE_H__
#define __PRIORITYQUEUE_H__

#include "List.h"
#include <SDL.h>
typedef struct PQueue_t
{
	List* list;

}PQueue;
PQueue* CreatePQueue(Uint32 size, size_t datasize);
void FreePQueue(PQueue* q);
ListElement PQueue_Dequeue(PQueue* q);
void PQueue_Enqueue(PQueue* q, void *data, Uint32 priority);
char* PQueue_AsArray(PQueue* q);

#endif