#include <SDL.h>
#include "gf2d_graphics.h"
#include "gf2d_sprite.h"
#include "simple_logger.h"
#include "PriorityQueue.h"

int main(int argc, char * argv[])
{
	slog("====================");
	/*
	PriorityQueue_t *q = CreatePriorityQueue(1);
	PriorityQueue_Enqueue(q, 'c', 3);
	PriorityQueue_Enqueue(q, 'a', 1);
	PriorityQueue_Enqueue(q, 'b', 2);
	PriorityQueue_Enqueue(q, 'd', 2);
	char c = PriorityQueue_Dequeue(q).data;
	char b = PriorityQueue_Dequeue(q).data;
	char d = PriorityQueue_Dequeue(q).data;
	char a = PriorityQueue_Dequeue(q).data;
	PriorityQueue_Enqueue(q, 'c', 1);
	PriorityQueue_Enqueue(q, 'd', 2);
	d = PriorityQueue_Dequeue(q).data;
	c = PriorityQueue_Dequeue(q).data;
	*/
	slog("====================");
	/*
	PriorityQueue *p = CreatePriorityQueue(10);
	char c = 'c';
	char a = 'a';
	char b = 'b';
	Insert(p, b, 2);
	Insert(p, c, 3);
	Insert(p, a, 1);
	*/
    /*variable declarations*/
	PriorityQueue_t *q = CreatePriorityQueue(1);

    int done = 0;
    const Uint8 * keys;
    Sprite *sprite;
	Vector2D lineEndpoint = vector2d(400, 0);
    int mx,my;
    float mf = 0;
    Sprite *mouse;
	Sprite* a, *b, *c, *d;
    Vector4D mouseColor = {255,100,255,200};
    
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
    gf2d_graphics_set_frame_delay(16);
    gf2d_sprite_init(1024);
    SDL_ShowCursor(SDL_DISABLE);
    
    /*demo setup*/
    sprite = gf2d_sprite_load_image("images/backgrounds/bg_flat.png");
    mouse = gf2d_sprite_load_all("images/pointer.png",32,32,16);
	/*Assignment 1 SetUp*/
	PriorityQueue_Enqueue(q, mouse, 1);
	PriorityQueue_Enqueue(q, mouse, 2);
	PriorityQueue_Enqueue(q, mouse, 2);
	PriorityQueue_Enqueue(q, mouse, 3);
	PriorityQueue_Enqueue(q, mouse, 3);
	PriorityQueue_Enqueue(q, mouse, 3);
	a = (Sprite*)PriorityQueue_Dequeue(q).data;
	b = (Sprite*)PriorityQueue_Dequeue(q).data;
	c = (Sprite*)PriorityQueue_Dequeue(q).data;
	d = (Sprite*)PriorityQueue_Dequeue(q).data;


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
			/*Assignment1*/
			gf2d_sprite_draw_image(a, vector2d(100, 100));
			gf2d_sprite_draw_image(b, vector2d(200, 200));
			gf2d_sprite_draw_image(c, vector2d(300, 300));
			gf2d_sprite_draw_image(d, vector2d(400, 400));

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
			//Jason
			gf2d_draw_line(vector2d(0,0),lineEndpoint,vector4d(255,0,0,100));
        gf2d_grahics_next_frame();// render current draw frame and skip to the next frame
        
        if (keys[SDL_SCANCODE_ESCAPE])done = 1; // exit condition
        slog("Rendering at %f FPS",gf2d_graphics_get_frames_per_second());
    }
    slog("---==== END ====---");
    return 0;
}
/*eol@eof*/
