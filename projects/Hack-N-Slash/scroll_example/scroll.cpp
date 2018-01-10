 //http://www.youtube.com/user/thecplusplusguy
//Thanks for the typed in code to Tapit85
//you need background.bmp (2000 x 480), tree_key.bmp

#if _WIN32
#include <SDL.h>
#include "SDL_image.h"
#else 
#include "SDL2/SDL_image.h"
#include <SDL2/SDL.h>
#endif

#include <iostream>

bool collision(SDL_Rect* rect1,SDL_Rect* rect2)
{
	if( rect1->y >= (rect2->y + rect2->h) ) // If rect1 is above rect2.
		return 0;
	if( rect1->x >= (rect2->x + rect2->w) ) // If rect1 is left of rect2.
		return 0;
	if( (rect1->y + rect1->h) <= rect2->y ) // If rect1 is below rect2.
		return 0;
	if( (rect1->x + rect1->w) <= rect2->x ) // If rect1 is right of rect2.
		return 0;
	return 1;
}

int width = 640;
int height = 480;

int main(int argc, char** argv)
{
	SDL_Init(SDL_INIT_EVERYTHING);
	
	SDL_Window *window = SDL_CreateWindow("Scrolling",
                          SDL_WINDOWPOS_UNDEFINED,
                          SDL_WINDOWPOS_UNDEFINED,
                          width, height,
                          0);

	SDL_Surface *screen, *background, *image;

	screen = SDL_GetWindowSurface(window);

	SDL_Renderer *GameRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);

	bool running = true;
	const int speed = 5;
	const int FPS = 30;
	Uint32 start;
	int x, y;
	x = 0;
	y = 0;

	background = SDL_LoadBMP( "background.bmp" );
	image = SDL_LoadBMP( "tree_key.bmp" );
	SDL_Rect imgloc = { 350, 170, 100, 100 };
	SDL_Rect camera;
	camera.x = 0;
	camera.y = 0;
	camera.w = 640;
	camera.h = 480;

	bool b[2] = { 0, 0 };
	while(running) {
		start = SDL_GetTicks();
		SDL_Event event;
		while( SDL_PollEvent( &event )) {
			switch( event.type ) {
				case SDL_QUIT:
					running = false;
					break;
				case SDL_KEYDOWN:
					switch(event.key.keysym.sym)
					{
						case SDLK_RIGHT:
							b[0] = 1;
							break;
						case SDLK_LEFT:
							b[1] = 1;
							break;
						case SDLK_ESCAPE:
							running = false;
							break;
					}
					break;
				case SDL_KEYUP:
					switch( event.key.keysym.sym )
					{
						case SDLK_RIGHT:
							b[0] = 0;
							break;
						case SDLK_LEFT:
							b[1] = 0;
							break;
					}
					break;
			}
		}

		//logic
		if( b[0] )
		{
			x += speed;
			camera.x += speed;
			if( camera.x >= 2000 - 640 )
				camera.x = 0;
		}
		else if( b[1] )
		{
			x -= speed;

			camera.x -= speed;
			if( camera.x <= 0 )
				camera.x = 2000 - 640;
		}

		SDL_Rect location = { x, y, 640, 480 };
		SDL_Rect relcoord = { imgloc.x - x, imgloc.y - y };

		//render
		SDL_RenderClear( GameRenderer );
		
		SDL_BlitSurface( background, &camera, screen, NULL );
		if( collision( &location, &imgloc ))
		{
			SDL_BlitSurface( image, NULL, screen, &relcoord );
		}

		SDL_SetRenderDrawColor( GameRenderer, 0, 255, 0, 255 );
		SDL_RenderDrawRect( GameRenderer, &camera );
		
		//SDL_Flip(screen);
		SDL_UpdateWindowSurface( window );
		SDL_RenderPresent( GameRenderer );

		if( 1000 / FPS > SDL_GetTicks() - start ) {
			SDL_Delay( 1000 / FPS - ( SDL_GetTicks() - start ));
		}
	}

	SDL_DestroyRenderer( GameRenderer );
	GameRenderer = NULL;
	SDL_FreeSurface( background );
	SDL_FreeSurface( image );
	SDL_Quit();
	return 0;
}