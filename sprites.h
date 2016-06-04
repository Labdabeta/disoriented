#ifndef SPRITES_H
#define SPRITES_H

#include <SDL2/SDL.h>

#include <string>

#include "graphics.h"

class Sprite
{// private:
        //friend class Graphics;
        SDL_Surface *surface;
        SDL_Texture *texture;
    public:
        Sprite(std::string filename);
        ~Sprite();

        void draw(Graphics &g, int left, int top, int width, int height);
};


#endif /* SPRITES_H */
