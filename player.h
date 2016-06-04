#ifndef PLAYER_H
#define PLAYER_H

#include "sprites.h"

class Player
{// private:
        Sprite imgs[4];
        int x,y;
        int dir; // 0 = up, 1 = right, 2 = down, 3 = left
        bool move; 
    public:
        Player();
        
        void onStep();
        void onDraw(Graphics &g, int tilesize);
        void onUp();
        void onDown();
        void onRight();
        void onLeft();

        int getX() { return x; }
        int getY() { return y; }
};
    
#endif /* PLAYER_H */
