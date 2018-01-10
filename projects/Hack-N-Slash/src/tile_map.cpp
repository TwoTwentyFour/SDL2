#if _WIN32
#include "SDL.h"
#else 
#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#endif

#include "tile_map.h"
#include "defines.h"

#include <fstream>

AV_Tile_Map::AV_Tile_Map()
{

	/*if ( TTF_Init() < 0)
	{
		printf( "TTF_Init Error: %s\n", TTF_GetError() );
		return;
	}*/

	srcRect.x = 0;
	srcRect.y = 0;
	srcRect.w = TILE_SIZE;
	srcRect.h = TILE_SIZE;

	dstRect.x = 0;
	dstRect.y = 0;
	dstRect.w = TILE_SIZE;
	dstRect.h = TILE_SIZE;

	backgroundSurface = NULL;
	optimizedBackgroundSurface = NULL;

	tileSurface = NULL;
	optimizedTileSurface = NULL;

	clr_black = { 0, 0, 0, 255 };
	font = NULL;
	textSurface = NULL;

}

// NOTE(Devan): Load background image from a .bmp file. Convert standard surface to an optimized surface.
void AV_Tile_Map::LoadBackgroundBMP( const char *backgroundBMPToLoad )
{
	if ( (backgroundSurface = SDL_LoadBMP( backgroundBMPToLoad )) )
	{
		if ( (optimizedBackgroundSurface = SDL_ConvertSurface( backgroundSurface, backgroundSurface->format, 0 )) )
		{
			// NOTE(Devan): Freeing this surface since we will be using the optimized surface..
			SDL_FreeSurface( backgroundSurface );
			backgroundSurface = NULL;
		}
		else
		{
			printf( "optimizedBackgroundSurface is NULL. %s\n", SDL_GetError() );
			return;
		}
	}
	else
	{
		printf( "Could not load image file. %s\n", SDL_GetError() );
		return;
	}
}

// NOTE(Devan): Blit the optimized back ground surface to the main screen surface.
void AV_Tile_Map::ShowBackgroundBMP( SDL_Rect *cameraRect, SDL_Surface *surfaceOfScreen )
{
	SDL_BlitSurface( optimizedBackgroundSurface, cameraRect, surfaceOfScreen, NULL );
}

void AV_Tile_Map::BackgroundCleanUp()
{
	SDL_FreeSurface( optimizedBackgroundSurface );
	optimizedBackgroundSurface = NULL;
}

SDL_Surface *AV_Tile_Map::GetOptimizedBackgroundSurface()
{
	return optimizedBackgroundSurface;
}

// NOTE(Devan): Load tile map from a .bmp file. Convert standard surface to an optimized surface.
void AV_Tile_Map::LoadTileMapBMP( const char *mapSheetToLoad )
{
	if ( (tileSurface = SDL_LoadBMP( mapSheetToLoad)) )
	{
		if ( (optimizedTileSurface = SDL_ConvertSurface( tileSurface, tileSurface->format, 0 )) )
		{
			// NOTE(Devan): Freeing this surface since we will be using the optimized surface.
			SDL_FreeSurface( tileSurface );
			tileSurface = NULL;
		}
		else
		{
			printf( "optimizedTileSurface is NULL. %s\n", SDL_GetError() );
			return;
		}
	}
	else
	{
		printf( "Could not load image file. %s\n", SDL_GetError() );
		return;
	}
}

// NOTE(Devan): Read tile information from a text file and store the datain a 2D vector.
void AV_Tile_Map::LoadMap( const char *fileToOpen )
{

	// NOTE(Devan): Opening the file.
	std::ifstream mapFile( fileToOpen );
	if( !mapFile.is_open() )
	{
		printf( "Error: Could not open file: %s\n", fileToOpen );
		return; // What does this do if not assigned a value?
	}

	// NOTE(Devan): Setting the dimensions of the map. The width and height are taken from the first two entries of the text file.
	unsigned int width = 0;
	unsigned int height = 0; 
	mapFile >> width;
	mapFile >> height;

	int current = 0;
	for( unsigned int y = 0; y < height; y++ )
	{
		// NOTE(Devan): Forming a new vector to be stored within the outer vector forming the rows of the map. 
		std::vector<int> innerVec;

		for( unsigned int x = 0; x < width; x++ )
		{
			if( mapFile.eof() )
			{
				printf( "Reached end of file %s too early. Check width and height parameters.\n", fileToOpen );
				return;
			}

			// NOTE(Devan): Capturing the value stored at the current location within the text file.
			mapFile >> current;

			// NOTE(Devan): Checking if the input is within the tile type boundaries. Current Types: ( 0 : 2 )
			if( current >= 0 && current <= 2 )
			{
				innerVec.push_back( current );
			}
			// NOTE(Devan): If the input is outside of the boundaries simply push 0 into the inner vector.
			else
			{
				innerVec.push_back(0);
			}
		}
		tileMap.push_back( innerVec );
	}

	mapFile.close();

}

// NOTE(Devan): Determine what tile image, if any, should be drawn to the tile map. 
void AV_Tile_Map::ShowMap()
{
	for( unsigned int y = 0; y < tileMap.size(); y++ )
	{
		for( unsigned int x = 0; x < tileMap[0].size(); x++ )
		{
			if( tileMap[y][x] == 1 )
			{

				srcRect.x = 0;
				srcRect.y = 0;

				dstRect.x = x * 60;
				dstRect.y = y * 60;
			}
			else if( tileMap[y][x] == 2 )
			{

				srcRect.x = 60;
				srcRect.y = 0;

				dstRect.x = x * 60;
				dstRect.y = y * 60;
			}	

			// NOTE(Devan): The srcRect is the image to draw from. The dstRect is the location to draw to.
			SDL_BlitSurface( optimizedTileSurface, &srcRect, optimizedBackgroundSurface, &dstRect );
		}
	}	
}

std::vector< std::vector< int >> AV_Tile_Map::GetTileMap()
{
	return tileMap;
}

void AV_Tile_Map::MapCleanUp()
{

	SDL_FreeSurface( optimizedTileSurface );
	optimizedTileSurface = NULL;

	// TTF_Quit();
}

/*// TODO(Devan): Set up text for ttf writing.
void AV_Tile_Map::TextSetup()
{
	// NOTE(Devan): Set up the text with font size 28 and text color black.
	clr_black = { 0, 0, 0, 255 };
	font = TTF_OpenFont( "fonts/lazy.ttf", 28 );
	if (  font == NULL )
	{
		printf( "Font returned NULL: %s\n", TTF_GetError() );
		return;
	}
}*/

// NOTE(Devan): Standard text output to the screen.
/*void AV_Tile_Map::OutputText( const char *textToWrite, SDL_Rect *dstRect, SDL_Surface *surfaceToWriteOn )
{
	textSurface = TTF_RenderText_Solid( font, textToWrite, clr_black );

	// NOTE(Devan): Show the text.
	SDL_BlitSurface( textSurface, dstRect, surfaceToWriteOn, NULL );
}*/

void AV_Tile_Map::TextCleanUp()
{
	//TTF_CloseFont( font );
    //	font = NULL;
	SDL_FreeSurface( textSurface );
	textSurface = NULL;	
}
