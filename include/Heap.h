#ifndef __HEAP_H_
#define __HEAP_H_
#include <SDL.h>

#include "List.h"

typedef struct Heap_t
{
	List* list;
}Heap;
Heap* Heap_Create(Uint32 size, size_t elementSize);
void Heap_Swap(ListElement *x, ListElement* y);
ListElement* Heap_GetParent(Heap* h, int index);
Heap* Heap_Insert(Heap* h, void* data, int priority);
ListElement* Heap_Left(Heap* h, int index);
ListElement* Heap_Right(Heap* h, int index);
ListElement Heap_RetrieveMax(Heap* h);
void Heap_Heapify(Heap* h,int index);
char* Heap_AsArray(Heap* heap);

#endif