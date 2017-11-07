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
}HashMap;
HashMap* HashMap_Create(int size, size_t dataSize);
unsigned long HashMap_Hash(unsigned char * key);
HashMap* HashMap_Insert(HashMap * h, const char * key, void * value);



unsigned long crc32(const unsigned char *s, unsigned int len);
#endif