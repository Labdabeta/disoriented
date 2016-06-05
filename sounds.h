#ifndef SOUNDS_H
#define SOUNDS_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

#include <string>

class Sound
{// private:
        Mix_Chunk *chunk;
    public:
        Sound(std::string filename);
        ~Sound();

        void play();
};

class Music
{// private:
        Mix_Music *music;
    public:
        Music(std::string filename);
        ~Music();

        void play();
};

#endif /* SOUNDS_H */
