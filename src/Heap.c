#include "Heap.h"
#include "simple_logger.h"

/**
* Heap Implementation
* Currently Heap_AsArray() function is not working but rest is!
*/
Heap* Heap_Create(Uint32 size, size_t elementSize)
{
	Heap* h = NULL;
	h = malloc(sizeof(Heap));
	memset(h, 0, sizeof(Heap));
	if (h != NULL)
	{
		h->list = List_Create(size, elementSize);
		if(h!= NULL)
			return h;
	}
	slog("Could not initialize Heap");
}
ListElement* Heap_Left(Heap* h, int index)
{
	if (2 * index + 1 > h->list->size)
	{
		return NULL;
	}
	return &h->list->list[2 * index  + 1];
}
ListElement* Heap_Right(Heap* h, int index)
{
	if (2 * index + 2 > h->list->size)
		return NULL;
	return &h->list->list[2 * index + 2];

}
void Heap_Swap(ListElement *x, ListElement* y)
{
	ListElement temp = *x;
	*x = *y;
	*y = temp;
}

ListElement* Heap_GetParent(Heap* h, int index)
{
	if (index == 0)
		return &h->list->list[0];
	return &h->list->list[(index - 1) / 2];
}
Heap* Heap_Insert(Heap* h, void* data, int priority)
{
	int i,parentIndex;
	ListElement* parent;
	ListElement temp;
	if (h->list->size == h->list->numElements)
	{
		slog("Overflow, could not add to heap");
		return;
	}
	i = h->list->numElements;
	List_Insert(h->list, data, i);
	i = h->list->numElements - 1;
	h->list->list[i].priority = priority;
	parentIndex = (i - 1) / 2;
	while (i != 0 && h->list->list[parentIndex].priority < h->list->list[i].priority)
	{
		Heap_Swap(&h->list->list[parentIndex], &h->list->list[i]);
		i = parentIndex;
		parentIndex = (i - 1) / 2;
		Heap_Heapify(h, 0);
	}
	return h;
}
void Heap_Heapify(Heap* h,int index)
{
	int largest;
	if (index < h->list->size)
	{
		ListElement* Left = Heap_Left(h, index);
		ListElement* Right = Heap_Right(h, index);
		if (Left != NULL)
		{
			largest = (Left->priority > h->list->list[index].priority) ? 2 * index + 1 : index;
		}
		else
			return;
		if (Right != NULL)
		{
			if (Right->priority > h->list->list[largest].priority)
				largest = 2 * index + 2;
		}
		if (h->list->list[largest].priority != h->list->list[index].priority)
		{
			Heap_Swap(&h->list->list[index], &h->list->list[largest]);
			Heap_Heapify(h, largest);
		}
	}
}

ListElement Heap_RetrieveMax(Heap* h)
{
	int i;
	ListElement Max;
	if (h != NULL)
	{
		Max = h->list->list[0];
		//Heap_Swap(&h->list->list[0], &h->list->list[h->list->numElements-1]);
//		List_Delete(h->list, h->list->numElements-1);
		List_Delete(h->list, 0);
		for (i = 0;i < h->list->numElements;i++)
		{
			Heap_Heapify(h, i);
		}
		return Max;
	}
}
char* Heap_AsArray(Heap* heap)
{
	int i;
	int numElements;
	List* newList;
	ListElement temp;
	newList = List_Create(heap->list->numElements, heap->list->typeSize);
	numElements = heap->list->numElements;
	for (i = 0; i < numElements;i++)
	{
		temp = Heap_RetrieveMax(heap);
		List_Insert(newList, temp.data, i);
	}
	return List_AsArray(newList);
}
