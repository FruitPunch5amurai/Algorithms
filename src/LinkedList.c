#include "simple_logger.h"
#include "LinkedList.h"


LinkedList * LinkedList_Create(size_t dataSize)
{
	LinkedList* l;
	l = (LinkedList*)malloc(sizeof(LinkedList));
	l->head = NULL;
	l->tail = NULL;
	l->dataSize = dataSize;
	l->numberOfElements = 0;
	return l;
}

LinkedList * LinkedList_Insert(LinkedList * l, void * data)
{
	LinkedListNode* n = NULL;
	LinkedListNode* current;
	if (l != NULL)
	{
		n = (LinkedListNode*)malloc(sizeof(LinkedListNode));
		if (n != NULL)
		{
			n->data = data;
			n->next = NULL;
			n->prev = NULL;
			if (l->head == NULL)
			{
				l->head = n;
				l->tail = n;
				l->numberOfElements++;
				return l;
			}
			l->tail->next = n;
			n->prev = l->tail;
			l->tail = n;
			l->numberOfElements++;
			return l;
		}
	}
}

LinkedList * LinkedList_InsertAtIndex(LinkedList * l, void * data, int index)
{
	LinkedListNode* n = NULL;
	LinkedListNode* current;
	int i;
	if (l != NULL)
	{
		if (index < l->numberOfElements)
		{
			current = l->head;
			n = (LinkedListNode*)malloc(sizeof(LinkedListNode));
			n->next = NULL;
			n->prev = NULL;
			n->data = data;
			for (i = 0; i < index; i++)
			{
				current = current->next;
			}
			n->prev = current->prev;
			n->next = current;
			if (current->prev != NULL)
			{
				current->prev->next = n;
			}
			current->prev = n;
			if (index == 0)
				l->head = n;
			else if (index == l->numberOfElements - 1)
				l->tail = n;
			l->numberOfElements++;
			return l;
		}
		slog("Linked List Index Out of Range");
	}
	slog("Linked List is NULL");
}

LinkedListNode * LinkedList_RemoveFromHead(LinkedList * l)
{
	LinkedListNode* n;

	if (l != NULL)
	{
		if (l->head != NULL)
		{
			n = l->head;
			l->head = n->next;
			l->head->prev = NULL;
			n->next = NULL;
			n->prev = NULL;
			l->numberOfElements--;
			return n;
		}
		slog("LinkedList Head is NULL");
	}
	slog("LinkedList is NULL");
}

LinkedListNode * LinkedList_RemoveFromTail(LinkedList * l)
{
	LinkedListNode* n;

	if (l != NULL)
	{
		if (l->tail != NULL)
		{
			n = l->tail;
			if (n->prev != NULL)
			{
				l->tail = n->prev;
				l->tail->next = NULL;
			}
			else
			{
				l->tail = NULL;
			}
			n->prev = NULL;
			l->numberOfElements--;
			return n;
		}
		slog("LinkedList Tail is NULL");
	}
	slog("LinkedList is NULL");
}

LinkedListNode * LinkedList_RemoveFromIndex(LinkedList * l, int index)
{
	LinkedListNode* n;
	int i;
	if (l != NULL)
	{
		if (l->numberOfElements > index)
		{
			n = l->head;
			for (i = 0; i < index; i++)
			{
				n = n->next;
			}
			if (index == 0)
				l->head = l->head->next;
			else if (index == l->numberOfElements - 1)
				l->tail = l->tail->prev;
			if (n->prev != NULL)
			{
				n->prev->next = n->next;
			}
			n->next->prev = n->prev;
			n->next = NULL;
			n->prev = NULL;
			l->numberOfElements--;
			return n;
		}
	}
}

void LinkedList_DeleteNode(LinkedListNode * node)
{
	free(node);
}

void LinkedList_DeleteList(LinkedList * n)
{
	LinkedListNode* node, *next;
	int i;
	node = n->head;
	for (i = 0;i < n->numberOfElements;i++)
	{
		next = node->next;
		free(node);
		node = next;
	}
	free(n);
}
