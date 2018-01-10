#include "audio.h"
#include <stdio.h>

AV_Audio::AV_Audio()
{
	// NOTE(Devan): Sound boared of effects and music to be used in the game.
	BackgroundWav = NULL;
	ScratchWav = NULL;
	LowWav = NULL;
	MidWav = NULL;
	HighWav = NULL;

	// NOTE(Devan): 22,050Hz.
	audioFrequency = 44100; 
	// NOTE(Devan): Signed 16bit Samples.
	audioFormat = MIX_DEFAULT_FORMAT;
	// NOTE(Devan): Sterio.
	audioChannels = 2;
	// NOTE(Devan): Bytes used per output line. 
	audioChunkSize = 2048; 

	// NOTE(Devan): Initialize SDL Mixer.
	if (	Mix_OpenAudio(	audioFrequency, audioFormat,
	                 audioChannels, audioChunkSize ) < 0 )
	{
		printf( "Mix_OpenAudio Error: %s\n", Mix_GetError() );
	}
}

// NOTE(Devan): Main Music.
void AV_Audio::PlayMusic_Background()
{
	BackgroundWav = Mix_LoadMUS( "sound/beat.wav" );
	if ( BackgroundWav == NULL )
	{
		printf( "Error Loading Music: %s\n", Mix_GetError() );
	}

	Mix_PlayMusic( BackgroundWav, -1 );
}

// NOTE(Devan): Sound effect 1.
void AV_Audio::PlaySoundEffect_Scratch()
{
	ScratchWav = Mix_LoadWAV( "sound/scratch.wav" );
	if ( ScratchWav == NULL )
	{
		printf( "Error Loading Sound Effects: %s\n", Mix_GetError() );
	}
	else
	{
		Mix_PlayChannel( -1, ScratchWav, 0 );
	}
}

// NOTE(Devan): Sound effect 2.
void AV_Audio::PlaySoundEffect_Low()
{
	LowWav = Mix_LoadWAV( "sound/low.wav" );
	if ( LowWav == NULL )
	{
		printf( "Error Loading Sound Effects: %s\n", Mix_GetError() );
	}
	else
	{
		Mix_PlayChannel( -1, LowWav, 0 );
	}
}

// NOTE(Devan): Sound effect 3.
void AV_Audio::PlaySoundEffect_Mid()
{
	MidWav = Mix_LoadWAV( "sound/mid.wav" );
	if ( MidWav == NULL )
	{
		printf( "Error Loading Sound Effects: %s\n", Mix_GetError() );
	}
	else
	{
		Mix_PlayChannel( -1, MidWav, 0 );
	}
}

// NOTE(Devan): Sound effect 4.
void AV_Audio::PlaySoundEffect_High()
{
	HighWav = Mix_LoadWAV( "sound/high.wav" );
	if ( HighWav == NULL )
	{
		printf( "Error Loading Sound Effects: %s\n", Mix_GetError() );
	}
	else
	{
		Mix_PlayChannel( -1, HighWav, 0 );
	}
}

void AV_Audio::StopMusic()
{
	Mix_HaltMusic();
}


void AV_Audio::AudioCleanUp()
{
	Mix_FreeMusic( BackgroundWav );
	Mix_FreeChunk( ScratchWav );
	Mix_FreeChunk( LowWav );
	Mix_FreeChunk( MidWav );
	Mix_FreeChunk( HighWav );

	BackgroundWav = NULL;
	ScratchWav = NULL;
	LowWav = NULL;
	MidWav = NULL;
	HighWav = NULL;

	Mix_Quit();
}