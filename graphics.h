#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#define TILES_PER_HEIGHT 15

extern int WIDTH;
extern int HEIGHT;
extern int TILE_SIZE;

class Graphics 
{// private:
        friend class Sprite;
        SDL_Window *window;
        SDL_Renderer *renderer;
        bool done;
    public:
        Graphics();
        ~Graphics();

        void run();

    protected:
        virtual bool onStep() = 0;
        virtual void onDraw() = 0;
        virtual void onA() = 0;
        virtual void onB() = 0;
        virtual void onC() = 0;
        virtual void onD() = 0;
        virtual void onE() = 0;
        virtual void onF() = 0;
        virtual void onUp() = 0;
        virtual void onDown() = 0;
        virtual void onRight() = 0;
        virtual void onLeft() = 0;
};

#endif /* GRAPHICS_H */
