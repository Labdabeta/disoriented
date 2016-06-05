#include "sounds.h"

Sound::Sound(std::string filename)
{
    chunk = Mix_LoadWAV(filename.c_str());
}

Sound::~Sound()
{
    Mix_FreeChunk(chunk);
}

void Sound::play() 
{
    Mix_PlayChannel(-1,chunk,0);
}

Music::Music(std::string filename)
{
    music = Mix_LoadMUS(filename.c_str());
}

Music::~Music()
{
    Mix_FreeMusic(music);
}

void Music::play()
{
    Mix_PlayMusic(music,-1);
}
