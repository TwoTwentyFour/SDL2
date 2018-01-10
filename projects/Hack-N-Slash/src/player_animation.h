#ifndef PLAYER_ANIMATION_H
#define PLAYER_ANIMATION_H

#include <vector>

class AV_Player_Animation
{

public:

	AV_Player_Animation();
	void LoadPlayerBMP();
	void ShowPlayer( SDL_Surface *dstSurface );
	int GetPlayerPosX();
	int GetPlayerPosY();
	void PlayerAnimationCleanUp();

 private:
 	
	int playerPosX;
	int playerPosY;
 	SDL_Surface *playerSurface;
 	SDL_Surface *optimizedPlayerSurface;
};

#endif
