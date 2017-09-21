
#include <SDL_image.h>

#include "simple_logger.h"
#include "gf2d_sprite.h"
#include "gf2d_text.h"
#include "gf2d_graphics.h"
#include "entity.h"
typedef struct
{
	Uint32 MaxEntities;
	Entity* entity_list;
}EntityManager;

static EntityManager entity_manager;

void EntityClose()
{
	EntityClearAll();
	if (entity_manager.entity_list != NULL)
	{
		free(entity_manager.entity_list);
	}
	entity_manager.entity_list = NULL;
	entity_manager.MaxEntities = 0;
	slog("EntitySystem closed");
}
void EntityInit(Uint32 max)
{
	if (!max)
	{
		slog("Cannot initialize a entity manager for zero entities!");
		return;
	}
	entity_manager.MaxEntities = max;
	entity_manager.entity_list = (Entity*)malloc(sizeof(Entity)*max);
	memset(entity_manager.entity_list, 0, sizeof(Entity)*max);
	slog("EntitySystem initialized");
	atexit(EntityClose);

}
void EntityFree(Entity* ent)
{
	if (!ent)
		return;
	if (ent->mSprite != NULL)
	{
		gf2d_sprite_free(ent->mSprite);
		ent->mSprite = NULL;
	}
	memset(ent, 0, sizeof(Entity));//clean up all other data
}

void EntityClearAll()
{
	int i;
	for (i = 0; i < entity_manager.MaxEntities;i++)
	{
		EntityFree(&entity_manager.entity_list[i]);
	}
}
Entity* EntityNew(Sprite* sprite,Vector2D pos)
{
	int i;
	Entity* ent = NULL;
	for (i = 0;i < entity_manager.MaxEntities;i++)
	{
		if (entity_manager.entity_list[i].ID == 0)
		{
			ent = &entity_manager.entity_list[i];
			ent->ID = i+1;
			break;
		}
	}
	ent->mSprite = sprite;
	ent->mPosition = pos;
	return ent;
}
void EntityDrawAll(int mf)
{
	int i;
	for (i = 0; i < entity_manager.MaxEntities; i++)
	{
		gf2d_sprite_draw(entity_manager.entity_list[i].mSprite, 
			entity_manager.entity_list[i].mPosition, NULL, NULL, NULL, NULL, &entity_manager.entity_list[i].mColor, (int)mf);
	}
}