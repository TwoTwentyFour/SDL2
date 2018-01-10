#ifdef _WIN32
#include "SDL.h"
#else
#include "SDL2/SDL.h"
#endif

// header
#ifndef QL_SESSION_H
#define QL_SESSION_H
class QL_Session
{
public:
	QL_Session( const int w, const int h );
	~QL_Session();

	bool QL_UpdateSurface();
	bool QL_CheckPollingState();
	bool keyWasPressed[101] = {};
	enum { ESC, SPACE, W, A, S, D };

	void QL_KeyboardInput( SDL_Event &event);
	SDL_Window* QL_GetSessionWindow() { return session_window; }
	SDL_Renderer* QL_GetSessionRenderer() { return session_renderer; }
	SDL_Surface* QL_GetSessionSurface() { return session_surface; }
private:
	SDL_Window *session_window;
	SDL_Renderer *session_renderer;
	SDL_Surface *session_surface;
	bool QL_SetupWindow( const int w, const int h );
	bool QL_SetupRenderer();
	bool QL_SetupSurface();

};
#endif

// implementation
#ifdef QL_SESSION
QL_Session::QL_Session( const int w, const int h )
{
	session_window = NULL;
	session_surface = NULL;
	QL_SetupWindow( w, h );
	QL_SetupRenderer();
}

QL_Session::~QL_Session()
{
	if ( session_surface != NULL )
	{
		SDL_FreeSurface( session_surface );	
		session_surface = NULL;
	}

	if ( session_renderer != NULL )
	{
		SDL_DestroyRenderer( session_renderer );
		session_renderer = NULL;
	}

	if ( session_window != NULL )
	{
		SDL_DestroyWindow( session_window ); 
		session_window = NULL;
	}

	SDL_Quit();	
}

bool QL_Session::QL_SetupWindow( const int w, const int h )
{
	bool result;
	if ( SDL_Init( SDL_INIT_EVERYTHING < 0 ))
	{
		SDL_Log( "SDL could not initialize. SDL Error: %s\n",
                          SDL_GetError() );
		result = false;
	}
	else
	{
		session_window = SDL_CreateWindow( "QL Session", 
                                                    SDL_WINDOWPOS_UNDEFINED, 
	                                            SDL_WINDOWPOS_UNDEFINED,
						    w, h,
                                                    SDL_WINDOW_RESIZABLE );
		if ( session_window == NULL )
		{
			SDL_Log( "SDL could not create window. SDL Error: %s\n",
                                  SDL_GetError() );
			result = false;
		}
		else
		{
			result = true;
		}
	}
return result;
}

bool	QL_Session::QL_SetupRenderer()
{
	bool result;
	session_renderer = SDL_CreateRenderer( session_window, -1, 0 );
	if ( session_renderer == NULL )
	{
		SDL_Log( "SDL could not create renderer. SDL Error: %s\n",
			  SDL_GetError() );
		result = false;
	}
	else
	{
		result = true;
	}
return result;
}

bool QL_Session::QL_SetupSurface()
{
	bool result;
	session_surface = SDL_GetWindowSurface( session_window );
	if ( session_surface == NULL )
	{
		SDL_Log( "SDL unable to create surface. SDL Error: %s\n", SDL_GetError() );
		result = false;
	}
	else
	{
		result = true;
	}
return result;
}

bool QL_Session::QL_UpdateSurface()
{
	bool result;
	if ( SDL_UpdateWindowSurface( session_window ) < 0 )
	{
		SDL_Log( "SDL could not update the surface. SDL Error: %s\n", 
                          SDL_GetError() );
		result = false;
	}
	else
	{
		result = true;
	}
return result;
}

// TODO: when using renderer, result gets set to false. WTF!?
// MSV error, result not set before returned...
/*bool QL_Session::QL_CheckPollingState()
{
	bool result;
	while ( SDL_PollEvent( &session_event ))
	{
		if ( session_event.type == SDL_QUIT ||
                     keyWasPressed[ESC] )
		{
			result = false;
			SDL_Log( "Hey Guy!\n" );
		}
		else 
		{
			QL_KeyboardInput( session_event );
			result = true;
		}
	}
return result;
}*/

void QL_Session::QL_KeyboardInput( SDL_Event &event )
{
	if ( event.type == SDL_KEYDOWN )
	{
		switch ( event.key.keysym.sym )
		{
			case SDLK_ESCAPE: keyWasPressed[ESC] = true; break;
			case SDLK_SPACE: keyWasPressed[SPACE] = true; break;
			case SDLK_w: keyWasPressed[W] = true; break;
			case SDLK_a: keyWasPressed[A] = true; break;
			case SDLK_s: keyWasPressed[S] = true; break;
			case SDLK_d: keyWasPressed[D] = true; break;
		}	
	}
	else if ( event.type == SDL_KEYUP )
	{
		switch ( event.key.keysym.sym )
		{
			case SDLK_ESCAPE: keyWasPressed[ESC] = false; break;
			case SDLK_SPACE: keyWasPressed[SPACE] = false; break;
			case SDLK_w: keyWasPressed[W] = false; break;
			case SDLK_a: keyWasPressed[A] = false; break;
			case SDLK_s: keyWasPressed[S] = false; break;
			case SDLK_d: keyWasPressed[D] = false; break;
		}	
	}
}
#endif
