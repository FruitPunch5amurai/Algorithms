#ifndef __STACK_H_
#define __STACK_H_

#include "List.h"
#include <SDL.h>

typedef struct Stack_t
{
	List* list;

}Stack;

Stack* Stack_Create(int initialSize, size_t dataType);
Stack* Stack_Push(Stack* s, void* data);
ListElement Stack_Pop(Stack* s);
ListElement Stack_Peep(Stack* s);
void Stack_Free(Stack* s);

#endif