#include "sprites.h"

Sprite::Sprite(std::string filename)
{
    surface = IMG_Load(filename.c_str());
    texture = NULL; // will be loaded later
}

Sprite::~Sprite()
{
    SDL_FreeSurface(surface);
}

void Sprite::draw(Graphics &g, int left, int top, int width, int height)
{
    if (texture == NULL) {
        texture = SDL_CreateTextureFromSurface(g.renderer,surface);
    }

    SDL_Rect r;
    r.x = left;
    r.y = top;
    r.w = width;
    r.h = height;
    SDL_RenderCopy(g.renderer,texture,NULL,&r);
}
