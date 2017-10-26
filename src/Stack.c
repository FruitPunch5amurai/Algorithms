#include "simple_logger.h"
#include "Stack.h"
/**
@brief Create Stack
*/
Stack* Stack_Create(int initialSize, size_t dataType)
{
	Stack* s;
	s = (Stack*)malloc(sizeof(Stack));
	if (s)
	{
		s->list = List_Create(initialSize, dataType);
		if (!s->list)
		{
			slog("Failed to Create List for Stack...");
			return NULL;
		}
		return s;
	}
	slog("Failed To Create Stack..");
	return NULL;
}
/**
@brief Push to Stack
*/
Stack* Stack_Push(Stack* s, void* data)
{
	if (s)
	{
		s->list = List_Insert(s->list, data, s->list->numElements);
		return s;
	}
	slog("Stack passed is null");
	return NULL;
}
/**
@brief Pop from stack
*/
ListElement Stack_Pop(Stack* s)
{
	ListElement e;
	if (s)
	{
		e = List_Get(s->list, s->list->numElements - 1);
		s->list = List_Delete(s->list, s->list->numElements - 1);
	}
	slog("Stack passed is null");
	return e;
}

ListElement Stack_Peep(Stack* s)
{
	if (s)
	{
		return List_Get(s->list, s->list->numElements - 1);
	};
	slog("Stack passed is null");
	return;
}
/**
@brief Free Stack
*/
void Stack_Free(Stack* s)
{
	if (s != NULL)
	{
		List_Free(s->list);
		free(s);
	}
}

