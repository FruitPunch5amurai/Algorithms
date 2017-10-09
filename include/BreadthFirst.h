#ifndef __BREADTHFIRST_H_
#define __BREADTHFIRST_H_

#include <SDL.h>
#include "List.h"
#include "TileMap.h"
#include "gf2d_vector.h"
#include "PriorityQueue.h"
typedef struct node_t
{
	int visited;
	int cameFrom;
}GraphNode;

typedef struct BreadthFirst_t {

	PQueue *frontier;
	TileMap *tileMap;
	GraphNode* nodes;
	List *path;
}BreadthFirst;

GraphNode* GraphNode_CreateGraph(TileMap* tilemap);
BreadthFirst* BreadthFirst_Create(TileMap* tilemap);
void BreadthFirst_GetPathToDestination(BreadthFirst* b);
void  BreadthFirst_MapOut(BreadthFirst* a, char tileToIgnore);
#endif