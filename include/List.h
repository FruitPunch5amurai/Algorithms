#ifndef __LIST_H_
#define __LIST_H_

#include <SDL.h>
typedef struct listelement_t
{
	void* data;
	Uint32 priority;

}ListElement;

typedef struct list_t
{
	ListElement* list;
	size_t typeSize;
	Uint32 size;
	Uint32 numElements;
}List;

List* List_Create(Uint32 size, size_t elementSize);
List* List_Insert(List* list, void* data, int index);
List* List_Delete(List* list, int index);
ListElement List_Get(List* list, int index);
void List_Free(List* list);
char* List_AsArray(List* list);

#endif