#ifndef __HASHMAP_H_
#define __HASHMAP_H_

#include "List.h"
typedef struct KV_Pair_t
{
	const char* key;
	void* value;
}KV_Pair;

typedef struct HashMap_t
{
	List* elementArray;
	Uint32 threshold;
	size_t dataSize;
}HashMap;
HashMap* HashMap_Create(int size, size_t dataSize);
void HashMap_DeleteMap(HashMap* m);
unsigned long HashMap_Hash(HashMap* h, unsigned char * key);
HashMap* HashMap_ReHash(HashMap* h);
HashMap* HashMap_Insert(HashMap * h, const char * key, void * value);
HashMap* HashMap_Remove(HashMap *h, const char * key);
void* HashMap_GetValue(HashMap *h, const char * key);


unsigned long crc32(const unsigned char *s, unsigned int len);
#endif