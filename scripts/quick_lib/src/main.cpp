#define QL_SESSION
#define QL_GAMEBLOCKS
#define QL_TIMERS
#include "ql_session.h"
#include "ql_gameblocks.h"
#include "ql_timer.h"

const int SCREEN_FPS = 60;
const int SCREEN_TICKS_PER_FRAME = 1000 / SCREEN_FPS;
const int SCREEN_WIDTH = 1040;
const int SCREEN_HEIGHT = 480;
const int CEN_X = SCREEN_WIDTH / 2; 
const int CEN_Y = SCREEN_HEIGHT / 2;

int main( int argc, char *argv[] )
{
	QL_Session *Session = new QL_Session( SCREEN_WIDTH, SCREEN_HEIGHT );
	SDL_Renderer *renderer = Session->QL_GetSessionRenderer();	
	QL_GameBlock *Player = new QL_GameBlock( 10, 10, 32, 32, 0, 0, 255 );
	int hspd, vspd;

	QL_Timer FPS_Timer;
	FPS_Timer.QL_StartTimer();
	QL_Timer CAP_Timer;
	int counted_frames = 0;
	int frame_ticks = 0;
	float average_fps = 0;

	bool is_running = true; 
	SDL_Event event;
	while ( is_running )
	{
		CAP_Timer.QL_StartTimer();
		while ( SDL_PollEvent(&event) )
		{
			Session->QL_KeyboardInput( event );
			if ( event.type == SDL_QUIT ||
                             Session->keyWasPressed[Session->ESC] )
			{
				is_running = false;
			} 
		}
		// set up timer for FPS
		average_fps = counted_frames / (FPS_Timer.QL_GetTicks() / 1000.0f);	
		if ( average_fps > 2000000 )
		{
			average_fps = 0;
		}
		SDL_Log( "Average FPS: %f", average_fps );  

		// set draw color and clear renderer
		SDL_SetRenderDrawColor( renderer, 0, 0, 0, SDL_ALPHA_OPAQUE );
		SDL_RenderClear( renderer );
		
		// move game blocks
		int player_speed = 6;
		vspd = (Session->keyWasPressed[Session->S] - Session->keyWasPressed[Session->W]) * player_speed; 
		hspd = (Session->keyWasPressed[Session->D] - Session->keyWasPressed[Session->A]) * player_speed; 
		Player->QL_MoveGameBlock( hspd, vspd );

		// draw things
		SDL_SetRenderDrawColor( renderer, 255, 255, 255, SDL_ALPHA_OPAQUE );
		SDL_RenderDrawLine( renderer, CEN_X, 0, CEN_X, SCREEN_HEIGHT );
		SDL_RenderDrawLine( renderer, 0, CEN_Y, SCREEN_WIDTH, CEN_Y );
	
		// draw wave
		SDL_SetRenderDrawColor( renderer, 0, 255, 0, SDL_ALPHA_OPAQUE );
		for ( int i = 0; i < 4; i++ )
		{
			if ( i % 2 == 0 )
			{
				SDL_RenderDrawLine( renderer, CEN_X + (100 * i), CEN_Y, CEN_X + (100 * (i + 1)), CEN_Y - 100 );	
				SDL_RenderDrawLine( renderer, CEN_X - (100 * i), CEN_Y, CEN_X - (100 * (i + 1)), CEN_Y + 100 );	
			}
			else
			{
				SDL_RenderDrawLine( renderer, CEN_X + (100 * i), CEN_Y - 100, CEN_X + ( 100 * (i + 1)), CEN_Y );	
				SDL_RenderDrawLine( renderer, CEN_X - (100 * i), CEN_Y + 100, CEN_X - ( 100 * (i + 1)), CEN_Y );	
			}
		}

		Player->QL_DrawGameBlock( renderer );

		// present the renderer
		SDL_RenderPresent( renderer );
		counted_frames++;

		// check and regulate frame rate
		frame_ticks = CAP_Timer.QL_GetTicks();
		if ( frame_ticks < SCREEN_TICKS_PER_FRAME )
		{
			SDL_Delay( SCREEN_TICKS_PER_FRAME - frame_ticks );
		}
	}

	SDL_DestroyRenderer( renderer );
	renderer = NULL;

	delete Player;
	Player = nullptr;
	Session->~QL_Session();
	delete Session;
	Session = nullptr;
return 0;
}
