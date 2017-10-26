#ifndef __BREADTHFIRST_H_
#define __BREADTHFIRST_H_

#include <SDL.h>
#include "List.h"
#include "TileMap.h"
#include "gf2d_vector.h"
#include "PriorityQueue.h"
#include "Graph.h"
typedef struct BreadthFirst_t {

	Graph* graph;
}BreadthFirst;

BreadthFirst* BreadthFirst_Create(TileMap* tilemap);
void  BreadthFirst_Free(BreadthFirst* b);
void  BreadthFirst_GetPathToDestination(BreadthFirst* b);
void  BreadthFirst_MapOut(BreadthFirst* a, char tileToIgnore);
void  BreadthFirst_ReturnPathAsVectors(BreadthFirst* b);
#endif