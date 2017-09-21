#ifndef __ENTITIY_H__
#define __ENTITIY_H__

#include "gf2d_sprite.h"
#include "gf2d_types.h"
typedef struct Entity_t
{
	Uint32 ID;
	Sprite *mSprite;
	Vector2D mPosition;
	Vector4D mColor;

}Entity;
Entity* EntityNew(Sprite* sprite, Vector2D pos);
void EntityDrawAll(int mf);
void EntityClose();
void EntityInit(Uint32 max);
void EntityFree(Entity * ent);
void EntityClearAll();
#endif