#include "player.h"
#include "defines.h"
#include "stdio.h"

AV_Player::AV_Player()
{
	screenCenX = SCR_WDT / 2;
	screenCenY = SCR_HGT / 2;
	playerX = screenCenX;
	playerY = screenCenY;
	camRect = { 0, 0, SCR_WDT, SCR_HGT };

	isPlayerMoving[UP] = false;
	isPlayerMoving[DOWN] = false;
	isPlayerMoving[LEFT] = false;
	isPlayerMoving[RIGHT] = false;

	inputX = 0;
	inputY = 0; 
}

void AV_Player::SetMoveDirection( SDL_Event event )
{
	if ( event.type == SDL_KEYDOWN )
	{
		switch( event.key.keysym.sym )
		{
			case SDLK_w:	
				isPlayerMoving[UP] = true;
			break;
			case SDLK_s:
				isPlayerMoving[DOWN] = true;
			break;
			case SDLK_a:
				isPlayerMoving[LEFT] = true;
			break;
			case SDLK_d:
				isPlayerMoving[RIGHT] = true;
			break;
		}
	}	
	else if ( event.type == SDL_KEYUP )
	{
		switch( event.key.keysym.sym )
		{
			case SDLK_w:	
				isPlayerMoving[UP] = false;
			break;
			case SDLK_s:
				isPlayerMoving[DOWN] = false;
			break;
			case SDLK_a:
				isPlayerMoving[LEFT] = false;
			break;
			case SDLK_d:
				isPlayerMoving[RIGHT] = false;
			break;
		}
	}
}

void AV_Player::SetMoveInput()
{
	if ( isPlayerMoving[UP] )
	{
		inputY = (PLAYER_VEL * -1);
	}
	else if ( isPlayerMoving[DOWN] )
	{
		inputY = PLAYER_VEL;
	}
	else if ( isPlayerMoving[LEFT] )
	{
		inputX = (PLAYER_VEL * -1);
	}
	else if ( isPlayerMoving[RIGHT] )
	{
		inputX = PLAYER_VEL;
	}
	else
	{
		inputY = 0;
		inputX = 0;
	}
}

void AV_Player::MovePlayer( std::vector<std::vector< int >> tileMap )
{ 		
	int newPlayerX = playerX + inputX;
	int newPlayerY = playerY + inputY;

	int playerRelX = (int)((newPlayerX + screenCenX) / TILE_SIZE); 
	int playerRelY = (int)((newPlayerY + screenCenY) / TILE_SIZE); 
	printf( "(%i, %i)\n", playerRelX, playerRelY );

	bool isValid = true;	
	if ( playerRelX >= 0 && playerRelX < LVL_WDT &&
	     playerRelY >= 0 && playerRelY < LVL_HGT )
	{	
		isValid = ( tileMap[playerRelY][playerRelX] == 0 ); 
	}

	if ( isValid )
	{
		playerX = newPlayerX;
		camRect.x = newPlayerX;		
		playerY = newPlayerY;
		camRect.y = newPlayerY;
	}
}
 
SDL_Rect AV_Player::GetCamRect()
{
	return camRect;
}

int AV_Player::GetCamX()
{
	return playerX;
}

int AV_Player::GetCamY()
{
	return playerY;
}

