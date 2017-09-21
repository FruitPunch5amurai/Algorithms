#include "Heap.h"
#include "simple_logger.h"
/*
Heap* CreateHeap(Uint32 size, size_t elementSize)
{
	Heap* h = NULL;
	h = malloc(sizeof(Heap));
	memset(h, 0, sizeof(Heap));
	if (h != NULL)
	{
		h->data = (element_t*)malloc(sizeof(element_t) * size);
		memset(h->data, 0, elementSize*size);
		h->size = size;
		h->elementSize = elementSize;
		return h;
	}
	slog("Could not initialize Heap");
}

void Heap_Swap(element_t *x, element_t* y)
{
	element_t temp = *x;
	*x = *y;
	*y = temp;
}
element_t* Heap_GetParent(Heap* h, int index)
{
	if (index == 0)
		return &h->data[0];
	return &h->data[(index - 1) / 2];
}
void MinHeap_Insert(Heap *h, void* data, int priority)
{
	int i;
	element_t* parent;
	element_t temp;
	if (h->size == h->numElements)
	{
		slog("Overflow, could not add to heap");
		return;
	}
	h->numElements++;
	i = h->numElements - 1;
	h->data[i].data = data;
	h->data[i].priority = priority;
	parent = Heap_GetParent(h, i);
	//Fix Max heap property if it is violated
	while (i != 0 && parent->priority > h->data[i].priority)
	{
		Heap_Swap(parent, &h->data[i]);
		i = Heap_GetParent(h,i)->priority;
	}
}

void* Heap_GetMax(Heap* h)
{

}
*/