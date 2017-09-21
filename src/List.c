#include "simple_logger.h"
#include "List.h"


List* List_Create(Uint32 size, size_t elementSize)
{
	List* l;
	if (size <= 0)
		return NULL;
	l = (List*)malloc(sizeof(List));
	memset(l, 0, sizeof(List));
	if (l != NULL);
	{
		l->list = malloc(sizeof(ListElement) * size);
		memset(l->list, 0, sizeof(ListElement)* size);
		l->typeSize = elementSize;
		l->size = size;
		return l;
	}
}

List* List_Insert(List* list,void* data, int index)
{
	if (list == NULL)
		return NULL;
	if (index <= list->size)
	{
		if(list->numElements >= list->size)
		{
			list->size = list->size * 2;
			list->list = (ListElement*)realloc(list->list, (list->size) * sizeof(ListElement));
			memset(&list->list[list->numElements], 0, sizeof(ListElement)* (list->size/2));
		}
		memmove(&list->list[index + 1], &list->list[index], sizeof(ListElement)*(list->numElements - index));
		list->list[index].data = data;
		list->numElements++;
		return list;
	}
	slog("List index is Larger than List size");
	return NULL;
}
List* List_Delete(List* list, int index)
{
	memmove(&list->list[index], &list->list[index + 1], sizeof(ListElement)*list->numElements);
	list->numElements--;
	memset(&list->list[list->numElements], 0, sizeof(ListElement)* (list->size - list->numElements));
	return list;
}
ListElement List_Get(List* list, int index)
{
	return list->list[index];
}
char* List_AsArray(List* list)
{	
	int i, numOfElements;
	char* ptr;
	char* data;
	numOfElements = list->numElements;
	data = malloc(list->typeSize * list->numElements);
	memset(data, 0, list->typeSize* list->numElements);
	ptr = data;
	for (i = 0;i < numOfElements;i++)
	{
		memcpy(ptr, list->list[i].data, list->typeSize);
		ptr = ptr + list->typeSize;
	}
	return data;
	
}

void List_Free(List* list)
{
	if (list != NULL)
	{
		if (list->list != NULL)
			free(list->list);
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
	free(list);
}