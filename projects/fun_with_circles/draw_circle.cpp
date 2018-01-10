#include "SDL.h"
#include <math.h>
#include <stdio.h>
#include "timer.h"

#define SCR_WDT  1280
#define SCR_HGT  960

const int SCR_CEN_X = SCR_WDT / 2;
const int SCR_CEN_Y = SCR_HGT / 2;

void DrawCenterCircle( SDL_Renderer *r, int x0, int y0, int rad );

int main ( int argc, char *argv[] )
{
	SDL_Init ( SDL_INIT_VIDEO ); 
	SDL_Window *window = SDL_CreateWindow ( "Drawing a Circle", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCR_WDT, SCR_HGT, 0 );
	SDL_Renderer *renderer = SDL_CreateRenderer ( window, -1, SDL_RENDERER_SOFTWARE );

	bool is_running = true;
	while ( is_running )
	{
		SDL_Event event;
		if ( SDL_PollEvent( &event ))
		{
			if ( event.type == SDL_QUIT )
			{
				is_running = false;
			}	
		}
	
		SDL_RenderClear ( renderer );
	
		DrawCenterCircle ( renderer, SCR_CEN_X, SCR_CEN_Y, 200 ); 

		SDL_SetRenderDrawColor ( renderer, 0, 0, 0, 255 );
		SDL_RenderPresent ( renderer );	
	}

	SDL_Quit ();

return 0; 
}

void DrawCenterCircle ( SDL_Renderer *r, int x0, int y0, int rad )
{
	int x = rad;
	int y = 0;
	int err = 0;

	SDL_SetRenderDrawColor ( r, 255, 255, 255, 255 );

	while ( x >= y )
	{
		SDL_RenderDrawPoint ( r, x0 + x, y0 + y ); // Octant 1, starting right of center, a distance equal to the radius and moving counter clockwise. 
		SDL_RenderDrawPoint ( r, x0 + y, y0 + x ); // Octant 2, starting at the final point of octant 1 and following the same track.
		SDL_RenderDrawPoint ( r, x0 - y, y0 + x ); // Octant 3.
		SDL_RenderDrawPoint ( r, x0 - x, y0 + y ); // Octant 4.
		SDL_RenderDrawPoint ( r, x0 - x, y0 - y ); // Octant 5.
		SDL_RenderDrawPoint ( r, x0 - y, y0 - x ); // Octant 6.
		SDL_RenderDrawPoint ( r, x0 + y, y0 - x ); // Octant 7.
		SDL_RenderDrawPoint ( r, x0 + x, y0 - y ); // Octant 8. The final point of octant 8 conects to the first point of octant 1. 

		y += 1;

		err += 1 + (2 * y);

		if ( 2 * (err - x) + 1 > 0)
		{
			x -= 1;
			err += 1 - (2 * x);
		}
	}
}
