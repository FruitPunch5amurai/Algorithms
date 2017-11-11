#include <SDL.h>
#include "gf2d_graphics.h"
#include "gf2d_sprite.h"
#include "simple_logger.h"
#include "DepthFirst.h"
#include "BreadthFirst.h"
#include "tilemap.h"
#include "Stack.h"
#include "HashMap.h"
#include "LinkedList.h"

int main(int argc, char * argv[])
{
    /*variable declarations*/
    int done = 0;
    const Uint8 * keys;
    Sprite *sprite;
	/*PathFinding Variables and for updating draw*/
	int counter = 0;
	int index = 0;
	Vector2D nextNode;

	Stack* stack;

    int mx,my;
    float mf = 0;
    Sprite *mouse;
    TileMap *map;
    Vector4D mouseColor = {0,0,255,200};
    static Vector2D path[2];
	/*Stack*/
    /*program initializtion*/
    init_logger("gf2d.log");
    slog("---==== BEGIN ====---");
    gf2d_graphics_initialize(
        "gf2d",
        1200,
        720,
        1200,
        720,
        vector4d(0,0,0,255),
        0);
    gf2d_graphics_set_frame_delay(17);
    gf2d_sprite_init(1024);
    SDL_ShowCursor(SDL_DISABLE);
    
    /*demo setup*/

    sprite = gf2d_sprite_load_image("images/backgrounds/bg_flat.png");
    mouse = gf2d_sprite_load_all("images/pointer.png",32,32,16);
    
    map = tilemap_load("levels/tilemap.map");
    vector2d_copy(path[0],map->start);
    vector2d_copy(path[1],map->end);
	/*Path Finding
	BreadthFirst* bFirst = BreadthFirst_Create(map);
	BreadthFirst_MapOut(bFirst, '1');
	BreadthFirst_GetPathToDestination(bFirst);
	BreadthFirst_ReturnPathAsVectors(bFirst);
	index = bFirst->graph->path->numElements -1;
	nextNode = bFirst->graph->pathVectors[index];
	*/
	/*Pathfinding*/
	DepthFirst* dFirst = DepthFirst_Create(map);
	DepthFirst_MapOut(dFirst, '1');
	DepthFirst_GetPathToDestination(dFirst);
	DepthFirst_ReturnPathAsVectors(dFirst);
	index = dFirst->graph->path->numElements - 1;
	nextNode = dFirst->graph->pathVectors[index];
	/*Stack	
	stack = Stack_Create(1, sizeof(char));
	Stack_Push(stack, 'a');
	Stack_Push(stack, 'b');
	Stack_Push(stack, 'c');
	char c = Stack_Pop(stack).data;
	char b = Stack_Pop(stack).data;
	char a = Stack_Pop(stack).data;
	*/
	/*HashMap Test*/
	HashMap* hashMap;
	hashMap = HashMap_Create(10, sizeof(char));
	hashMap = HashMap_Insert(hashMap, "KI", "ABC");
	hashMap = HashMap_Insert(hashMap, "AA", "DEF");
	hashMap = HashMap_Insert(hashMap, "BB", "GHI");
	hashMap = HashMap_Insert(hashMap, "CC", "JKL");
	hashMap = HashMap_Insert(hashMap, "DD", "MNO");

	char* KI = HashMap_GetValue(hashMap, "KI");
	char* AA = HashMap_GetValue(hashMap, "AA");
	char* BB = HashMap_GetValue(hashMap, "BB");
	char* CC = HashMap_GetValue(hashMap, "CC");
	char* DD = HashMap_GetValue(hashMap, "DD");
	hashMap = HashMap_Remove(hashMap, "KI");
	char* b = HashMap_GetValue(hashMap, "KI");
	slog(KI);
	//	ListElement *e = List_GetPtr(hashMap->elementArray, 6);
//	LinkedList* ll = (LinkedList*)e->data;
	/*main game loop*/
    while(!done)
    {
        SDL_PumpEvents();   // update SDL's internal event structures
        keys = SDL_GetKeyboardState(NULL); // get the keyboard state for this frame
        /*update things here*/
        SDL_GetMouseState(&mx,&my);
        mf+=0.1;
        if (mf >= 16.0)mf = 0;
        
        gf2d_graphics_clear_screen();// clears drawing buffers
        // all drawing should happen betweem clear_screen and next_frame
            //backgrounds drawn first
            gf2d_sprite_draw_image(sprite,vector2d(0,0));
                        
            tilemap_draw(map,vector2d(86,24));
            tilemap_draw_path(path,2, map,vector2d(86,24));
			counter++;
			if (counter > 15)
			{
				index--;
				if (index >= 0)
				{
					nextNode = dFirst->graph->pathVectors[index];
					counter = 0;
				}
			}
			//Player Draw
			gf2d_sprite_draw(
				map->tileset,
				vector2d(vector2d(86, 24).x+ (nextNode.x * map->tileset->frame_w), vector2d(86, 24).y + (nextNode.y *map->tileset->frame_h)),
				NULL,
				NULL,
				NULL,
				NULL,
				NULL,
				2);
			//UI elements last
            gf2d_sprite_draw(
                mouse,
                vector2d(mx,my),
                NULL,
                NULL,
                NULL,
                NULL,
                &mouseColor,
                (int)mf);
        gf2d_grahics_next_frame();// render current draw frame and skip to the next frame
        
        if (keys[SDL_SCANCODE_ESCAPE])done = 1; // exit condition
   //     slog("Rendering at %f FPS",gf2d_graphics_get_frames_per_second());
    }
    slog("---==== END ====---");
	//BreadthFirst_Free(bFirst);
	DepthFirst_Free(dFirst);
	HashMap_DeleteMap(hashMap);
	//Stack_Free(stack);
	return 0;
}
/*eol@eof*/
