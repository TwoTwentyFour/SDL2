#ifndef RENDERER_H
#define RENDERER_H

#if _WIN32
#include "SDL_image.h"
#else 
#include "SDL2/SDL_image.h"
#endif

class AV_Renderer
{

public:

	AV_Renderer( SDL_Window *GameWindow );
	SDL_Renderer *GetGameRenderer();
	void UpdateRenderer();
	void RenderCleanUp();

private:
	
	SDL_Renderer *GameRenderer;
};

#endif