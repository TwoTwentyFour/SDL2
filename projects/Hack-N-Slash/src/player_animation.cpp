#if _WIN32
#include "SDL.h"
#else 
#include "SDL2/SDL.h"
#endif

#include "stdio.h"
#include "defines.h"
#include "player_animation.h"

AV_Player_Animation::AV_Player_Animation()
{
	// NOTE(Devan): Used for moving the player rect before it touches any of the walls of the camPlayerBox.
	playerPosX = (SCR_WDT / 2) - (PLAYER_WDT / 2);
	playerPosY = (SCR_HGT / 2) - PLAYER_HGT; 
	
	optimizedPlayerSurface = NULL;
	playerSurface = NULL;

}

// NOTE(Devan): Load player image from a .bmp file. Convert standard surface to an optimized surface.
void AV_Player_Animation::LoadPlayerBMP()
{
	if ( (playerSurface = SDL_LoadBMP( "art/player.bmp" )) )
	{
		if ( (optimizedPlayerSurface = SDL_ConvertSurface( playerSurface, playerSurface->format, 0 )) )
		{
			// NOTE(Devan): Freeing this surface since we will be using the optimized surface.
			SDL_FreeSurface( playerSurface );
			playerSurface = NULL;
		}
		else
		{
			printf( "optimizedPlayerSurface is NULL. %s\n", SDL_GetError() );
			return;
		}
	}
	else
	{
		printf( "Could not load image file. %s\n", SDL_GetError() );
		return;
	}

	unsigned int colorKey = SDL_MapRGB( optimizedPlayerSurface->format, 255, 0, 255 );
	SDL_SetColorKey(	optimizedPlayerSurface, SDL_TRUE, colorKey );
}

// NOTE(Devan): Blit the palyer image to the target surface.
void AV_Player_Animation::ShowPlayer( SDL_Surface *dstSurface )
{
	SDL_Rect playerRect;
	playerRect.w = PLAYER_WDT;
	playerRect.h = PLAYER_HGT;
	playerRect.x = playerPosX;
	playerRect.y = playerPosY;

	SDL_BlitSurface( optimizedPlayerSurface, NULL, dstSurface, &playerRect );
}

void AV_Player_Animation::PlayerAnimationCleanUp()
{
	SDL_FreeSurface( optimizedPlayerSurface );
	optimizedPlayerSurface = NULL;
}

