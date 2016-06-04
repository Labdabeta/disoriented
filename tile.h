#ifndef TILE_H
#define TILE_H

#include "sprites.h"

class Tile
{// private:
    public:
        static Sprite *tile;
        Tile(bool up, bool left, bool down, bool right, int x, int y);
        // wall presence
        bool up,left,down,right;
        int x,y;
        void draw(Graphics &g, int px, int py, int tsize);
}; 

#endif /* TILE_H */
