#ifndef __GRAPH_H_
#define __GRAPH_H_

#include <SDL.h>
#include "List.h"
#include "TileMap.h"
#include "gf2d_vector.h"

typedef struct node_t
{
	int visited;
	int cameFrom;
}GraphNode;

typedef struct Graph_t {

	void* frontier;
	TileMap *tileMap;
	GraphNode* nodes;
	List *path;
	Vector2D* pathVectors;
}Graph;

GraphNode* GraphNode_CreateGraph(TileMap* tilemap);
#endif