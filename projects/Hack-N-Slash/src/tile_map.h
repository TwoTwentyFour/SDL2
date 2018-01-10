#ifndef TILE_MAP_H
#define TILE_MAP_H

#include <stdio.h>
#include <vector>

#include "SDL2/SDL_ttf.h"

class AV_Tile_Map
{
	
public:

	AV_Tile_Map();

	void LoadBackgroundBMP( const char *backgroundBMPToLoad );
	SDL_Surface *GetOptimizedBackgroundSurface();
	void ShowBackgroundBMP(	SDL_Rect *cameraRect,  SDL_Surface *surfaceOfScreen );
	void BackgroundCleanUp();

	void LoadTileMapBMP( const char *mapSheetToLoad );
	void LoadMap( const char *fileToOpen );
	void ShowMap();
	std::vector< std::vector< int >> GetTileMap();
	void MapCleanUp();
	
	void TextSetup();
	void OutputText( const char *textToWrite, SDL_Rect *dstRect, SDL_Surface *surfaceToWriteOn );
	void TextCleanUp();
	
private:
	
	std::vector< std::vector< int >> tileMap;
	SDL_Rect srcRect;
	SDL_Rect dstRect;

	SDL_Surface *optimizedBackgroundSurface;
	SDL_Surface *backgroundSurface;

	SDL_Surface *optimizedTileSurface;
	SDL_Surface *tileSurface;

	SDL_Color clr_black;
	TTF_Font *font;
	SDL_Surface *textSurface;
	

};

#endif
