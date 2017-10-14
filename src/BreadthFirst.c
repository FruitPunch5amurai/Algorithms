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

void BreadthFirst_Free(BreadthFirst* b)
{

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
		//a->frontier = CreatePQueue(tilemap->width * tilemap->height, sizeof(Vector2D));
		a->path = List_Create(tilemap->width * tilemap->height, sizeof(int));
		a->tileMap = tilemap;
		start = tilemap->start.x + (tilemap->width * tilemap->start.y);
		PQueue_Enqueue(a->frontier, start, a->frontier->list->numElements);
		//PQueue_Enqueue(a->frontier, &tilemap->start, a->frontier->list->numElements);
		a->nodes = GraphNode_CreateGraph(tilemap);
		return a;
	}
	else
	{
		slog("TileMap is null");
		return NULL;
	}
}
void  BreadthFirst_Delete(BreadthFirst* b)
{
	if (b->frontier)
		FreePQueue(b->frontier);
	if (b->path)
		List_Free(b->path);
	if (b->nodes)
		free(b->nodes);
	if (b->pathVectors)
		free(b->pathVectors);
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
			//PQueue_Enqueue(a->frontier, &topVec, order);
			a->nodes[top].visited = 1;
			a->nodes[top].cameFrom = current;
		}
		if (left >= 0 && a->nodes[left].visited != 1 && a->tileMap->map[left] != tileToIgnore)
		{
			PQueue_Enqueue(a->frontier, left, order);
			//PQueue_Enqueue(a->frontier, &leftVec, order);
			a->nodes[left].visited = 1;
			a->nodes[left].cameFrom = current;
		}
		if (bottom < (a->tileMap->width * a->tileMap->height) && a->nodes[bottom].visited != 1 && a->tileMap->map[bottom] != tileToIgnore)
		{
			PQueue_Enqueue(a->frontier, bottom, order);
			//PQueue_Enqueue(a->frontier, &bottomVec, order);
			a->nodes[bottom].visited = 1;
			a->nodes[bottom].cameFrom = current;
		}
		if (right < (a->tileMap->width * a->tileMap->height) && a->nodes[right].visited != 1 && a->tileMap->map[right] != tileToIgnore)
		{
			PQueue_Enqueue(a->frontier, right, order);
			//PQueue_Enqueue(a->frontier, &rightVec, order);
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
	int nextY;
	int nextX;
	int newPos;
	start = b->tileMap->start.x + (b->tileMap->width * b->tileMap->start.y);
	current = b->tileMap->end.x + (b->tileMap->width * b->tileMap->end.y);
	List_Insert(b->path, current, b->path->numElements);
	while (current != start)
	{
		newPos = b->nodes[current].cameFrom;
		List_Insert(b->path, newPos, b->path->numElements);
		current = newPos;
	}
	slog("Breadth First Pathfinding Complete...");
}
void BreadthFirst_ReturnPathAsVectors(BreadthFirst* b)
{
	Vector2D *pos;
	pos = (Vector2D*)malloc(sizeof(Vector2D) * b->path->numElements);
	for (int i = 0; i < b->path->numElements;i++)
	{
		int newPos = b->path->list[i].data;
		pos[i].y = newPos / b->tileMap->width;
		pos[i].x = newPos - (b->tileMap->width * pos[i].y);
	}
	b->pathVectors = pos;
	slog("Breadth First Returned Path as Vectors...");
}