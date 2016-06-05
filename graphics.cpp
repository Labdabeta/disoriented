#include "graphics.h"
#include <iostream>
#define GAME_NAME "Astray and Adrift"

int WIDTH;
int HEIGHT;
int TILE_SIZE;

#define WIN_WIDTH 1920
#define WIN_HEIGHT 1080
#define FPS 60
//#define WIN_WIDTH 1050
//#define WIN_HEIGHT 750

Graphics::Graphics() {
    SDL_Init(SDL_INIT_EVERYTHING);

    IMG_Init(IMG_INIT_PNG);

    window = SDL_CreateWindow(
            GAME_NAME,
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            WIN_WIDTH,
            WIN_HEIGHT,
            SDL_WINDOW_SHOWN|SDL_WINDOW_FULLSCREEN_DESKTOP);


    renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
    SDL_GetRendererOutputSize(renderer,&WIDTH,&HEIGHT);
    TILE_SIZE = HEIGHT/TILES_PER_HEIGHT;
    std::cout<<"Real resolution: "<<WIDTH<<"x"<<HEIGHT<<":"<<TILE_SIZE<<std::endl;
    SDL_SetRenderDrawColor(renderer,0x0,0x0,0x0,0xFF);
    done = false;
}

Graphics::~Graphics() {
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
}

void Graphics::run() {
    int ticks = SDL_GetTicks();
    int tcount = 0;
    SDL_Event e;
    while (!done) {
        while (SDL_PollEvent(&e)) {
            switch (e.type) {
                case SDL_QUIT:
                    done=true;
                    break;
                case SDL_KEYDOWN:
                    switch (e.key.keysym.sym) {
                        case 'a': onA(); break;
                        case 'b': onB(); break;
                        case SDLK_SPACE: onB(); break;
                        case 'c': onC(); break;
                        /*case 'd': onD(); break;
                        case 'e': onE(); break;
                        case 'f': onF(); break;*/
                        case SDLK_UP: onUp(); break;
                        case SDLK_DOWN: onDown(); break;
                        case SDLK_LEFT: onLeft(); break;
                        case SDLK_RIGHT: onRight(); break;
                    }
                    break;
            }
            if (e.type == SDL_QUIT) {
                done = true;
            }
        }

        if (tcount > 20) {
            done |= onStep();
            tcount = 0;
        }

        SDL_RenderClear(renderer);
        onDraw();
        SDL_RenderPresent(renderer);

        int now = SDL_GetTicks();
        if (now - ticks < (1000/FPS)) {
            SDL_Delay((1000/FPS)-(now-ticks));
        }

        ticks = now;
        tcount++;
    }
}
