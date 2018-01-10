#if _WIN32
#include "SDL.h"
#else 
#include "SDL2/SDL.h"
#endif

#include "defines.h"
#include "window.h"
#include "renderer.h"
#include "player.h"
#include "tile_map.h"
#include "player_animation.h"

int main( int argc, char *argv[] )
{

	// NOTE(Devan): Setting up all in-game objects.
	AV_Window Window;
	Window.CreateWindowAndScreenSurface();
	SDL_Window *window = Window.GetGameWindow();
	SDL_Surface *screen = Window.GetScreenSurface();

	AV_Renderer Renderer( window );
	SDL_Renderer *renderer = Renderer.GetGameRenderer();

	AV_Player Player;
	AV_Player_Animation PlayerAnim;
	PlayerAnim.LoadPlayerBMP();

	AV_Tile_Map LevelOneTileMap;
	LevelOneTileMap.LoadTileMapBMP( "art/tileMapSheet.bmp" );
	LevelOneTileMap.LoadBackgroundBMP( "art/background.bmp" );
	LevelOneTileMap.LoadMap( "tilemap.map" );
	// LevelOneTileMap.TextSetup();
	
	// NOTE(Devan): Setting up game variables.
	SDL_Rect camRect;
	std::vector< std::vector< int >> tileMap;

	// NOTE(Devan): Beginning the main game loop.
	bool isRunning = true;
	SDL_Event event;
	while( isRunning )
	{
		
		while( SDL_PollEvent( &event ) != 0 )
		{
			// NOTE(Devan): Check for game quit condition.
			if ( event.type == SDL_QUIT )
			{
	 			isRunning = false;
 			}

	 		Player.SetMoveDirection( event );
 		}

		// NOTE(Devan): Set up variables for referance. 
		camRect = Player.GetCamRect();

		SDL_RenderClear( renderer );

		// NOTE(Devan) Show background image and tile map and setup isSolid vector..
		LevelOneTileMap.ShowBackgroundBMP( &camRect, screen );
		// LevelOneTileMap.OutputText( "TEST", &camRect, screen );
		LevelOneTileMap.ShowMap();
		tileMap = LevelOneTileMap.GetTileMap();

		// NOTE(Devan): Move the player and camera.
 		Player.SetMoveInput();	
		Player.MovePlayer( tileMap );

		// NOTE(Devan): Show playerAnim.
		PlayerAnim.ShowPlayer( screen );

		// NOTE(Devan): Update Window and Renderer and draw the empty spaces black.
		SDL_SetRenderDrawColor( renderer, 0, 0, 0, 255 );
		SDL_UpdateWindowSurface( window );	
		Renderer.UpdateRenderer();
	}	

	// NOTE(Devan): Clean Up.
	PlayerAnim.PlayerAnimationCleanUp();
	LevelOneTileMap.TextCleanUp();
	LevelOneTileMap.BackgroundCleanUp();
	LevelOneTileMap.MapCleanUp();
	Renderer.RenderCleanUp();
	Window.WindowCleanUp();
	SDL_Quit();

    return 0;
}
