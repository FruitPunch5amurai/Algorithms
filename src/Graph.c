#include "simple_logger.h"
#include "Graph.h"

GraphNode* GraphNode_CreateGraph(TileMap* tilemap)
{
	GraphNode* nodes = NULL;

	nodes = (GraphNode*)malloc(sizeof(GraphNode) * (tilemap->height * tilemap->width));
	if (nodes == NULL)
	{
		slog("Failed to create GraphNode");
		return;
	}
	memset(nodes, 0, sizeof(int)*(tilemap->height * tilemap->width));
}
