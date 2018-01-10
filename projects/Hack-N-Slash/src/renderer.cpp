#include "renderer.h"
#include "window.h"
#include <stdio.h>

// NOTE(Devan): Create the main game renderer. 
AV_Renderer::AV_Renderer( SDL_Window *GameWindow )
{
	GameRenderer = SDL_CreateRenderer( GameWindow, -1, SDL_RENDERER_SOFTWARE );
	if ( GameRenderer == NULL )
	{
		printf( "GameRenderer returned NULL: %s\n", IMG_GetError() );
		return;
	}
}

// NOTE(Devan): Get a renderer we can use in the game.
SDL_Renderer *AV_Renderer::GetGameRenderer()
{
	if ( GameRenderer == NULL )
	{
		printf( " The game renderer returned NULL.%s\n", IMG_GetError() );
		return 0;
	}

	return GameRenderer;
}

// NOTE(Devan): Show elements being rendered.
void AV_Renderer::UpdateRenderer()
{
	SDL_RenderPresent( GameRenderer );
}

void AV_Renderer::RenderCleanUp()
{
	SDL_DestroyRenderer( GameRenderer );
	GameRenderer = NULL;
}