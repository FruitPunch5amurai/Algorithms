#include "simple_logger.h"
#include "BreadthFirst.h"

BreadthFirst* BreadthFirst_Create(TileMap* tilemap)
{
	BreadthFirst* a = NULL;
	int start;
	if (tilemap)
	{
		a = (BreadthFirst*)malloc(sizeof(BreadthFirst));
		memset(a, 0, sizeof(BreadthFirst));
		a->graph = (Graph*)malloc(sizeof(Graph));

		a->graph->frontier = CreatePQueue(tilemap->width * tilemap->height, sizeof(int));
		a->graph->path = List_Create(tilemap->width * tilemap->height, sizeof(int));
		a->graph->tileMap = tilemap;
		start = tilemap->start.x + (tilemap->width * tilemap->start.y);
		PQueue* queue= a->graph->frontier;
		PQueue_Enqueue(a->graph->frontier, start, queue->list->numElements);
		a->graph->nodes = GraphNode_CreateGraph(tilemap);
		return a;
	}
	else
	{
		slog("TileMap is null");
		return NULL;
	}
}

void  BreadthFirst_Free(BreadthFirst* b)
{
	if (b->graph->frontier)
		FreePQueue(b->graph->frontier);
	if (b->graph->path)
		List_Free(b->graph->path);
	if (b->graph->nodes)
		free(b->graph->nodes);
	if (b->graph->pathVectors)
		free(b->graph->pathVectors);
	free(b->graph);
	free(b);
}
void  BreadthFirst_MapOut(BreadthFirst* a, char tileToIgnore)
{

	int top;
	int bottom;
	int right;
	int left;
	int current;
	ListElement l;
	int order = a->graph->tileMap->width * a->graph->tileMap->height;
	PQueue* queueFrontier = a->graph->frontier;
	while (queueFrontier->list->numElements != 0)
	{
		l = PQueue_Dequeue(queueFrontier);
		//Get Neighbors
		current = (int)l.data;
		a->graph->nodes[current].visited = 1;

		top = current - a->graph->tileMap->width;
		bottom = current + a->graph->tileMap->width;
		left = current - 1;
		right = current + 1;
		
		if (current == 196)
		{
			slog("Hello!");
		}
		if (top >= 0 && a->graph->nodes[top].visited != 1 && a->graph->tileMap->map[top] != tileToIgnore)
		{
			PQueue_Enqueue(queueFrontier, top, order);
			//PQueue_Enqueue(a->frontier, &topVec, order);
			a->graph->nodes[top].visited = 1;
			a->graph->nodes[top].cameFrom = current;
		}
		if (left >= 0 && a->graph->nodes[left].visited != 1 && a->graph->tileMap->map[left] != tileToIgnore)
		{
			PQueue_Enqueue(queueFrontier, left, order);
			//PQueue_Enqueue(a->frontier, &leftVec, order);
			a->graph->nodes[left].visited = 1;
			a->graph->nodes[left].cameFrom = current;
		}
		if (bottom < (a->graph->tileMap->width * a->graph->tileMap->height) && a->graph->nodes[bottom].visited != 1 && a->graph->tileMap->map[bottom] != tileToIgnore)
		{
			PQueue_Enqueue(queueFrontier, bottom, order);
			//PQueue_Enqueue(a->frontier, &bottomVec, order);
			a->graph->nodes[bottom].visited = 1;
			a->graph->nodes[bottom].cameFrom = current;
		}
		if (right < (a->graph->tileMap->width * a->graph->tileMap->height) && a->graph->nodes[right].visited != 1 && a->graph->tileMap->map[right] != tileToIgnore)
		{
			PQueue_Enqueue(queueFrontier, right, order);
			//PQueue_Enqueue(a->frontier, &rightVec, order);
			a->graph->nodes[right].visited = 1;
			a->graph->nodes[right].cameFrom = current;
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
	start = b->graph->tileMap->start.x + (b->graph->tileMap->width * b->graph->tileMap->start.y);
	current = b->graph->tileMap->end.x + (b->graph->tileMap->width * b->graph->tileMap->end.y);
	List_Insert(b->graph->path, current, b->graph->path->numElements);
	while (current != start)
	{
		newPos = b->graph->nodes[current].cameFrom;
		List_Insert(b->graph->path, newPos, b->graph->path->numElements);
		current = newPos;
	}
	slog("Breadth First Pathfinding Complete...");
}

void BreadthFirst_ReturnPathAsVectors(BreadthFirst* b)
{
	Vector2D *pos;
	pos = (Vector2D*)malloc(sizeof(Vector2D) * b->graph->path->numElements);
	for (int i = 0; i < b->graph->path->numElements;i++)
	{
		int newPos = b->graph->path->list[i].data;
		pos[i].y = newPos / b->graph->tileMap->width;
		pos[i].x = newPos - (b->graph->tileMap->width * pos[i].y);
	}
	b->graph->pathVectors = pos;
	slog("Breadth First Returned Path as Vectors...");
}