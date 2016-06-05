#include <SDL2/SDL.h>

#include "graphics.h"
#include "maze.h"

#define INIT_W 30
#define INIT_H 30
#define INIT_D 0.55
#define INIT_E 1
//#define INIT_W 40
//#define INIT_H 40
//#define INIT_D 0.4
//#define INIT_E 2

#define DELTA_W 5
#define DELTA_H 5
#define DELTA_D 0.05
#define DELTA_E 1

#define START_SCREEN "Start_Legend.png"
#define RETRY_SCREEN_PHANTASM "Retry_Option.png"
#define BITCH_SCREEN_PHANTASM "Quit_Option.png"
#define RETRY_SCREEN_MRHUGGZ "MrHuggz_Game_Over_Retry.png"
#define BITCH_SCREEN_MRHUGGZ "MrHuggz_Game_Over_Quit.png"
#define RETRY_SCREEN_WALL "WallMon_Game_Over_Retry.png"
#define BITCH_SCREEN_WALL "WallMon_Game_Over_Quit.png"
#define RETRY_SCREEN_SPIDER "Spider_Game_Over_Quit.png"
#define BITCH_SCREEN_SPIDER "Spider_Game_Over_Quit.png"


class AstrayAndAdrift : public Graphics
{// private:
    Maze maze;
    int w,h,e;
    int level;
    double d;
    int why; //why'd you die?
    int state; // 0 = start, 1 = playing, 2 = retry, 3 = bitch, 4 = quit
    Sprite start,retry[4],bitch[4];
    int getD() { if (why == -1) return 0; return why; }
    public:
        AstrayAndAdrift() : 
            maze(INIT_W,INIT_H,INIT_D,INIT_E,0),
            start(START_SCREEN),
            retry({Sprite(RETRY_SCREEN_MRHUGGZ),Sprite(RETRY_SCREEN_PHANTASM),Sprite(RETRY_SCREEN_WALL),Sprite(RETRY_SCREEN_SPIDER)}),
            bitch({Sprite(BITCH_SCREEN_MRHUGGZ),Sprite(BITCH_SCREEN_PHANTASM),Sprite(BITCH_SCREEN_WALL),Sprite(BITCH_SCREEN_SPIDER)})
        {
            w = INIT_W;
            h = INIT_H;
            d = INIT_D;
            e = INIT_E;
            level = 0;
            state = 0;
        }
        bool onStep() { 
            if (state == 1) {
                maze.onStep(); 
                
                if (maze.winner()) {
                    w += DELTA_W;
                    h += DELTA_H;
                    if (level % 2) e += DELTA_E; else d -= DELTA_D;
                    level++;

                    maze.reset(w,h,d,e,level);
                    return false;
                }

                if (why = maze.dead()) {
                    state = 2;
                }
                return false; 
            }
            return state == 4;
        }
        void onDraw() { 
            switch (state) {
                case 0: start.draw(*this,0,0,WIDTH,HEIGHT); break;
                case 1: maze.onDraw(*this); break;
                case 2: retry[getD()].draw(*this,0,0,WIDTH,HEIGHT); break;
                case 3: bitch[getD()].draw(*this,0,0,WIDTH,HEIGHT); break;
            }
        }
        void onA() { 
            switch (state) {
                case 0: maze.male(true); state = 1; break;
                case 1: maze.onA(); break;
                case 2: 
                    w = INIT_W; 
                    h = INIT_H;
                    d = INIT_D;
                    e = INIT_E;
                    level = 0;
                    maze.reset(w,h,d,e,level); 
                    state = 1; 
                    break;
                case 3: 
                    state = 4; 
                    break;
            }
        }
        void onB() { 
            if (state == 0) { maze.male(false); state = 1; }
            if (state == 1) { maze.onB(); } 
        }
        void onC() {
            w += DELTA_W;
            h += DELTA_H;
            e += DELTA_E;
            d -= DELTA_D;
            level++;

            maze.reset(w,h,d,e,level);
        }
        void onD() {}
        void onE() {}
        void onF() {}
        void onUp() { 
            if (state == 1) maze.onUp(); 
            else if (state == 3) state = 2;
        }
        void onDown() { 
            if (state == 1) maze.onDown(); 
            else if (state == 2) state = 3;
        }
        void onRight() { if (state == 1) maze.onRight(); }
        void onLeft() { if (state == 1) maze.onLeft(); }
};

int main(int argc, char *argv[])
{
    AstrayAndAdrift g;

    g.run();

    return 0;
}
