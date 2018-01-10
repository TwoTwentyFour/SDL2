#include "SDL.h"
#include <math.h>
#include <stdio.h>

#define SCR_WDT  1280
#define SCR_HGT  960

const int SCR_CEN_X = SCR_WDT / 2;
const int SCR_CEN_Y = SCR_HGT / 2;

void DrawCircle( SDL_Renderer *r, int x, int y, int rad );

enum { UP, DOWN, LEFT, RIGHT };

struct Circle
{
	int radius;
	int x;
	int y;	
};

int main ( int argc, char *argv[] )
{
	SDL_Init ( SDL_INIT_VIDEO ); 
	SDL_Window *window = SDL_CreateWindow ( "Drawing a Circle", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCR_WDT, SCR_HGT, 0 );
	SDL_Renderer *renderer = SDL_CreateRenderer ( window, -1, SDL_RENDERER_SOFTWARE );

	Circle cir1;
	cir1.radius = 150;
	cir1.x = SCR_CEN_X;
	cir1.y = SCR_CEN_Y;

	Circle cir2;
 	cir2.radius = 50;
	cir2.x = 50;
	cir2.y = 50;

	bool is_moving[4];
	for ( int i = 0; i < sizeof( is_moving ); i++ )
	{
		is_moving[i] = false;
	}	

	bool is_running = true;
	while ( is_running )
	{
		SDL_Event event;
		while( SDL_PollEvent( &event ) != 0 )
		{
			if ( event.type == SDL_QUIT )
			{
				is_running = false;
			}	
			else if ( event.type == SDL_KEYDOWN )
			{
				switch ( event.key.keysym.sym )
				{
					case SDLK_w: is_moving[UP] = true; break;
					case SDLK_s: is_moving[DOWN] = true; break;
					case SDLK_a: is_moving[LEFT] = true; break;
					case SDLK_d: is_moving[RIGHT] = true; break;
				}
			}
			else if ( event.type == SDL_KEYUP )
			{
				switch ( event.key.keysym.sym )
				{
					case SDLK_w: is_moving[UP] = false; break;
					case SDLK_s: is_moving[DOWN] = false; break;
					case SDLK_a: is_moving[LEFT] = false; break;
					case SDLK_d: is_moving[RIGHT] = false; break;
				}
			}
		}

		cir2.x += (is_moving[RIGHT] - is_moving[LEFT]) * 2;
		cir2.y += (is_moving[DOWN] - is_moving[UP]) * 2;
		
		int distance_x = (cir1.x - cir2.x);
		int distance_y = (cir1.y - cir2.y);
		int total_radius = (cir1.radius + cir2.radius);
 
		if ( abs ( distance_x ) < total_radius && 
		     abs ( distance_y ) < total_radius )  
		{
			printf ( "hit\n" );
		}
		
		printf ( "(%d, %d)\n", cir2.x, cir2.y );

		SDL_RenderClear ( renderer );

		DrawCircle ( renderer, cir1.x, cir1.y, cir1.radius );
		DrawCircle ( renderer, cir2.x, cir2.y, cir2.radius );

		SDL_SetRenderDrawColor ( renderer, 0, 0, 0, 255 );
		SDL_RenderPresent ( renderer );	}

	SDL_Quit ();

return 0; 
}

void DrawCircle( SDL_Renderer *r, int x, int y, int rad )
{
	int radius = rad; 
	int new_x = 0;
	int new_y = 0;
	// float final_theta = (M_PI * 2);
	// int old_x = x + (radius * cos ( final_theta )); 
	// int old_y = y - (radius * sin ( final_theta )); 
	float step = (M_PI * 2) / 50; 

	SDL_SetRenderDrawColor ( r, 255, 255, 255, 255 );
	
	for ( float theta = 0.0f; theta <= (M_PI * 2); theta += step )
	{
		new_x = x + (radius * cos ( theta ));
		new_y = y - (radius * sin ( theta ));	
		
		SDL_RenderDrawPoint ( r, new_x, new_y );
		
	//	old_x = new_x;
	//	old_y = new_y;
	}

 /*	new_x = x + (radius * cos ( final_theta )); 
	new_y = y - (radius * sin ( final_theta ));	
	SDL_RenderDrawLine( r, old_x, old_y, new_x, new_y ); */

}

