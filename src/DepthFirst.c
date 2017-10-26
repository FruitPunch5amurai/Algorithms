#include "simple_logger.h"
#include "DepthFirst.h"



DepthFirst* DepthFirst_Create(TileMap* tilemap)
{
	DepthFirst* a = NULL;
	int start;
	if (tilemap)
	{
		a = (DepthFirst*)malloc(sizeof(DepthFirst));
		memset(a, 0, sizeof(DepthFirst));
		a->graph = (Graph*)malloc(sizeof(Graph));

		a->graph->frontier = Stack_Create(tilemap->width * tilemap->height, sizeof(int));
		a->graph->path = List_Create(tilemap->width * tilemap->height, sizeof(int));
		a->graph->tileMap = tilemap;
		start = tilemap->start.x + (tilemap->width * tilemap->start.y);
		Stack* stack = a->graph->frontier;
		Stack_Push(a->graph->frontier, start);
		a->graph->nodes = GraphNode_CreateGraph(tilemap);
		return a;
	}
	else
	{
		slog("TileMap is null");
		return NULL;
	}

}
void  DepthFirst_Free(DepthFirst* b)
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
void  DepthFirst_MapOut(DepthFirst* d, char tileToIgnore)
{
	Stack* stackFrontier;
	int top;
	int bottom;
	int right;
	int left;
	int current;
	ListElement l;

	stackFrontier = d->graph->frontier;
	int order = d->graph->tileMap->width * d->graph->tileMap->height;
	while (stackFrontier->list->numElements != 0)
	{
		l = Stack_Pop(stackFrontier);
		current = (int)l.data;
		d->graph->nodes[current].visited = 1;

		top = current - d->graph->tileMap->width;
		bottom = current + d->graph->tileMap->width;
		left = current - 1;
		right = current + 1;
		if (top >= 0 && d->graph->nodes[top].visited != 1 && d->graph->tileMap->map[top] != tileToIgnore)
		{
			Stack_Push(stackFrontier, top);
			d->graph->nodes[top].cameFrom = current;
		}
		if (left >= 0 && d->graph->nodes[left].visited != 1 && d->graph->tileMap->map[left] != tileToIgnore)
		{
			Stack_Push(stackFrontier, left);
			d->graph->nodes[left].cameFrom = current;
		}
		if (bottom >= 0 && d->graph->nodes[bottom].visited != 1 && d->graph->tileMap->map[bottom] != tileToIgnore)
		{
			Stack_Push(stackFrontier, bottom);
			d->graph->nodes[bottom].cameFrom = current;
		}
		if (right >= 0 && d->graph->nodes[right].visited != 1 && d->graph->tileMap->map[right] != tileToIgnore)
		{
			Stack_Push(stackFrontier, right);
			d->graph->nodes[right].cameFrom = current;
		}
		order--;
	}
}

void  DepthFirst_GetPathToDestination(DepthFirst* d)
{
	int current;
	int start;
	int nextY;
	int nextX;
	int newPos;
	start = d->graph->tileMap->start.x + (d->graph->tileMap->width * d->graph->tileMap->start.y);
	current = d->graph->tileMap->end.x + (d->graph->tileMap->width * d->graph->tileMap->end.y);
	List_Insert(d->graph->path, current, d->graph->path->numElements);
	while (current != start)
	{
		newPos = d->graph->nodes[current].cameFrom;
		List_Insert(d->graph->path, newPos, d->graph->path->numElements);
		current = newPos;
	}
	slog("Depth First Pathfinding Complete...");
}

void  DepthFirst_ReturnPathAsVectors(DepthFirst* d)
{
	Vector2D *pos;
	pos = (Vector2D*)malloc(sizeof(Vector2D) * d->graph->path->numElements);
	for (int i = 0; i < d->graph->path->numElements;i++)
	{
		int newPos = d->graph->path->list[i].data;
		pos[i].y = newPos / d->graph->tileMap->width;
		pos[i].x = newPos - (d->graph->tileMap->width * pos[i].y);
	}
	d->graph->pathVectors = pos;
	slog("Breadth First Returned Path as Vectors...");
}
