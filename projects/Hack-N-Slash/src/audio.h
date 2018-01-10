#ifndef AUDIO_H
#define AUDIO_H

#if _WIN32
#include "SDL_mixer.h"
#else 
#include "SDL2/SDL_mixer.h"
#endif

class AV_Audio
{

public:

	AV_Audio();
	void PlayMusic_Background();
	void PlaySoundEffect_Scratch();
	void PlaySoundEffect_Low();
	void PlaySoundEffect_Mid();
	void PlaySoundEffect_High();
	void StopMusic();
	void AudioCleanUp();
	
private:
	
	int audioFrequency;
	unsigned int audioFormat;
	int audioChannels;
	int audioChunkSize;
	Mix_Music *BackgroundWav;
	Mix_Chunk *ScratchWav;
	Mix_Chunk *LowWav;
	Mix_Chunk *MidWav;
	Mix_Chunk *HighWav;
};

#endif
