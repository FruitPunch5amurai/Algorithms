#ifndef __DEPTHFIRST_H_
#define __DEPTHFIRST_H_

#include <SDL.h>
#include "List.h"
#include "TileMap.h"
#include "gf2d_vector.h"
#include "Graph.h"
#include "Stack.h"

typedef struct DepthFirst_t{

	Graph* graph;

}DepthFirst;
DepthFirst* DepthFirst_Create(TileMap* tilemap);
void  DepthFirst_Free(DepthFirst* b);
void  DepthFirst_GetPathToDestination(DepthFirst* d);
void  DepthFirst_MapOut(DepthFirst* d, char tileToIgnore);
void  DepthFirst_ReturnPathAsVectors(DepthFirst* d);

#endif
