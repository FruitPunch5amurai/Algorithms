#ifndef __LINKEDLIST_H_
#define __LINKEDLIST_H_

#include <SDL.h>
typedef struct LinkedListNode_t
{
	void* data;
	struct LinkedListNode_t* next;
	struct LinkedListNode_t* prev;
}LinkedListNode;
typedef struct LinkedList_t
{
	LinkedListNode *head;
	LinkedListNode *tail;
	size_t dataSize;
	int numberOfElements;
}LinkedList;

LinkedList* LinkedList_Create(size_t dataSize);
LinkedList* LinkedList_Insert(LinkedList* l, void * data);
LinkedList* LinkedList_InsertAtIndex(LinkedList* l, void * data,int index);
LinkedListNode* LinkedList_RemoveFromHead(LinkedList* l);
LinkedListNode* LinkedList_RemoveFromTail(LinkedList* l);
LinkedListNode* LinkedList_RemoveFromIndex(LinkedList* l,int index);
void LinkedList_DeleteNode(LinkedListNode* node);
void LinkedList_DeleteList(LinkedList* n);
#endif

