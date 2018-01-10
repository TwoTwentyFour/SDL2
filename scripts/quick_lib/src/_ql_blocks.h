#ifdef _WIN32
#include "SDL.h"
#else
#include "SDL2/SDL.h"
#endif

// header file section
#ifndef QL_BLOCKS_H
#define QL_BLOCKS_H
struct GameBlock
{
	SDL_Rect block;
	unsigned int color;
};
#endif

// implementation section
#ifdef QL_BLOCKS
GameBlock QL_CreateGameBlock( int w, int h, int x, int y, 
                              unsigned int c )
{
	GameBlock new_gb;
	new_gb.block.w = w;
	new_gb.block.h = h;
	new_gb.block.x = x;
	new_gb.block.y = y;
	new_gb.color = c;

return new_gb;
}

void QL_DrawGameBlocks( GameBlock gb[], SDL_Surface *s )
{
	for ( int i = 0; i < sizeof( gb ); i++ )
	{
	 	SDL_FillRect( s, &gb[i].block, gb[i].color ); 
	}	
}

bool QL_CollisionCheck( SDL_Rect &r1, SDL_Rect &r2 )
{
	bool result = false;
	if ( (r1.x + r1.w) >= r2.x &&
             (r1.y + r1.h) >= r2.y &&
	      r1.x <= (r2.x + r2.w) &&
              r1.y <= (r2.y + r2.h) )
	{
		result = true;
	}

return result;
}

void QL_MoveBlock( int vspd, int hspd, GameBlock &gb )
{
	gb.block.x += vspd;
	gb.block.y += hspd;
}

void QL_ClampBlockToArea( int w, int h, GameBlock &gb )
{
	if ( gb.block.x <= 0 )
	{
		gb.block.x = 0;
	}
	else if ( (gb.block.x + gb.block.w) >= w )
	{
		gb.block.x = (w - gb.block.w);
	}
	
	if ( gb.block.y <= 0 )
	{
		gb.block.y = 0;
	}
	else if ( (gb.block.y + gb.block.h) >= h )
	{
		gb.block.y = (h - gb.block.h);
	}	
}

void QL_ClampBlockToBlock(  GameBlock &gb1, GameBlock &gb2 )
{
	if ( gb1.block.x <= gb2.block.x )
	{
		gb1.block.x = gb2.block.x;
	}
	else if ( (gb1.block.x + gb1.block.w) >= (gb2.block.x + gb2.block.w) )
	{
		gb1.block.x = (gb2.block.x + gb2.block.w) - gb1.block.w;
	}

	if ( gb1.block.y <= gb2.block.y )
	{
		gb1.block.y = gb2.block.y;
	}
	else if ( (gb1.block.y + gb1.block.h) >= (gb2.block.y + gb2.block.h) )
	{
		gb1.block.y = (gb2.block.y + gb2.block.h) - gb1.block.h;
	}
}
#endif
