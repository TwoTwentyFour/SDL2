#ifndef PLAYER_H
#define PLAYER_H

#if _WIN32
#include "SDL.h"
#else 
#include "SDL2/SDL.h"
#endif

#include "defines.h"

#include <vector>

class AV_Player
{
	
public:

	AV_Player();
	void SetMoveDirection( SDL_Event even );
	void SetMoveInput();
	void MovePlayer( std::vector<std::vector< int >> tileMap );
	SDL_Rect GetCamRect();
	int GetCamX();
	int GetCamY();

private:
	
	SDL_Rect camRect;
	int screenCenX;
	int screenCenY;
	int playerX;
	int playerY;
	int inputX;
	int inputY;
	bool isPlayerMoving[4];
};

#endif
