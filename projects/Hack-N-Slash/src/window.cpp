#include "window.h"
#include "defines.h"

#include <stdio.h>

#define NOT_USING_FLAGS 0

AV_Window::AV_Window()
{
	gameWindow = NULL;
	screenSurface = NULL;
}

// NOTE(Devan): Setting up the window and the main screen surface for drawing.
void AV_Window::CreateWindowAndScreenSurface()
{
	if( SDL_Init(SDL_INIT_EVERYTHING) < 0 )
	{
		printf( "SDL_Init Error: %s\n", SDL_GetError() );
		return;
	}

	gameWindow = SDL_CreateWindow( "Hack Away!!",
								SDL_WINDOWPOS_UNDEFINED,
								SDL_WINDOWPOS_UNDEFINED,
								SCR_WDT, SCR_HGT, NOT_USING_FLAGS ); // <----- Check This Out!!	SDL_WINDOW_FULLSCREEN
	if( gameWindow == NULL )
	{
		printf( "The game window returned NULL: %s\n", SDL_GetError() );
		return;
	}

	screenSurface = SDL_GetWindowSurface( gameWindow );
}

SDL_Window *AV_Window::GetGameWindow()
{
	if( gameWindow == NULL )
	{
		printf( "Window still NULL: %s\n", SDL_GetError() );
		return NULL;
	}

	return gameWindow;
}

SDL_Surface *AV_Window::GetScreenSurface()
{
	if( screenSurface == NULL)
	{
		printf(	"The screen surface returned NULL: %s\n", SDL_GetError() );
		return NULL;
	}

	return screenSurface;
}

void AV_Window::WindowCleanUp()
{	
	SDL_FreeSurface( screenSurface );
	screenSurface = NULL;
	SDL_DestroyWindow( gameWindow );
	gameWindow = NULL;
}