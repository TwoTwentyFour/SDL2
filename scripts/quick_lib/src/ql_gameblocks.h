#ifdef _WIN32
#include "SDL.h"
#else
#include "SDL2/SDL.h"
#endif

// header
#ifndef QL_GAMEBLOCKS_H
#define QL_GAMEBLOCKS_H
class QL_GameBlock
{
public:
	QL_GameBlock( int x, int y, int w, int h, 
                      Uint8 r, Uint8 g, Uint8 b );	
	~QL_GameBlock();
	void QL_DrawGameBlock( SDL_Renderer *r );
	void QL_MoveGameBlock( int hspd, int vspd );
	SDL_Rect game_block;
private:
	Uint8 red_val;
	Uint8 green_val;
	Uint8 blue_val;
};
#endif

// implementation
#ifdef QL_GAMEBLOCKS
QL_GameBlock::QL_GameBlock( int x, int y, int w, int h, 
                            Uint8 r, Uint8 g, Uint8 b )
{
	game_block.x = x;
	game_block.y = y;
	game_block.w = w;
	game_block.h = h;
	red_val = r;
	green_val = g;
	blue_val = b;
}

QL_GameBlock::~QL_GameBlock()
{
}

void QL_GameBlock::QL_DrawGameBlock( SDL_Renderer *r )
{
	SDL_SetRenderDrawColor( r, red_val, green_val, blue_val,
                                SDL_ALPHA_OPAQUE );
	SDL_RenderFillRect( r, &game_block );
}

void QL_GameBlock::QL_MoveGameBlock( int hspd, int vspd )
{
	game_block.x += hspd;
	game_block.y += vspd;	
}
#endif
