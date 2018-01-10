#ifndef WINDOW_H 
#define WINDOW_H 

#if _WIN32
#include "SDL.h"
#else 
#include "SDL2/SDL.h"
#endif

class AV_Window
{

public:

	AV_Window();
	void CreateWindowAndScreenSurface();
	SDL_Window *GetGameWindow();
	SDL_Surface *GetScreenSurface();
	void WindowCleanUp();
	
private:
	
	SDL_Window *gameWindow;
	SDL_Surface *screenSurface;
};

#endif 
