#include "simple_logger.h"
#include "BreadthFirst.h"

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
BreadthFirst* BreadthFirst_Create(TileMap* tilemap)
{
	BreadthFirst* a = NULL;
	int start;
	if (tilemap)
	{
		a = (BreadthFirst*)malloc(sizeof(BreadthFirst));
		memset(a, 0, sizeof(BreadthFirst));
		a->frontier = CreatePQueue(tilemap->width * tilemap->height, sizeof(int));
		a->path = List_Create(tilemap->width * tilemap->height, sizeof(int));
		a->tileMap = tilemap;
		start = tilemap->start.x + (tilemap->width * tilemap->start.y);
		PQueue_Enqueue(a->frontier, start, a->frontier->list->numElements);
		a->nodes = GraphNode_CreateGraph(tilemap);
		return a;
	}
	else
	{
		slog("TileMap is null");
		return NULL;
	}
}
void  BreadthFirst_MapOut(BreadthFirst* a, char tileToIgnore)
{

	int top;
	int bottom;
	int right;
	int left;
	int current;
	ListElement l;
	int order = a->tileMap->width * a->tileMap->height;
	while (a->frontier->list->numElements != 0)
	{
		l = PQueue_Dequeue(a->frontier);
		//Get Neighbors
		current = (int)l.data;
		a->nodes[current].visited = 1;

		top = current - a->tileMap->width;
		bottom = current + a->tileMap->width;
		left = current - 1;
		right = current + 1;
		if (current == 196)
		{
			slog("Hello!");
		}
		if (top >= 0 && a->nodes[top].visited != 1 && a->tileMap->map[top] != tileToIgnore)
		{
			PQueue_Enqueue(a->frontier, top, order);
			a->nodes[top].visited = 1;
			a->nodes[top].cameFrom = current;
		}
		if (left >= 0 && a->nodes[left].visited != 1 && a->tileMap->map[left] != tileToIgnore)
		{
			PQueue_Enqueue(a->frontier, left, order);
			a->nodes[left].visited = 1;
			a->nodes[left].cameFrom = current;
		}
		if (bottom < (a->tileMap->width * a->tileMap->height) && a->nodes[bottom].visited != 1 && a->tileMap->map[bottom] != tileToIgnore)
		{
			PQueue_Enqueue(a->frontier, bottom, order);
			a->nodes[bottom].visited = 1;
			a->nodes[bottom].cameFrom = current;
		}
		if (right < (a->tileMap->width * a->tileMap->height) && a->nodes[right].visited != 1 && a->tileMap->map[right] != tileToIgnore)
		{
			PQueue_Enqueue(a->frontier, right, order);
			a->nodes[right].visited = 1;
			a->nodes[right].cameFrom = current;
		}
		order--;
	}
	slog("Breadth First Map Out Complete...");
}
void BreadthFirst_GetPathToDestination(BreadthFirst* b)
{
	int current;
	int start;

	start = b->tileMap->start.x + (b->tileMap->width * b->tileMap->start.y);
	current = b->tileMap->end.x + (b->tileMap->width * b->tileMap->end.y);
	List_Insert(b->path, current, b->path->numElements);
	while (current != start)
	{
		current = b->nodes[current].cameFrom;
		List_Insert(b->path, current, b->path->numElements);
	}
	slog("Breadth First Pathfinding Complete...");
}
