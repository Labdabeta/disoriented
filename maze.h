#ifndef MAZE_H
#define MAZE_H

#include "player.h"
#include "sprites.h"

#include <vector>

#define TILE_SIZE 50

struct Tile {
    bool up,left,down,right;
};

class Maze 
{// private:
        //dir is 0 = up, 1 = right, 2 = down, 3 = left
        int player_x,player_y,player_dir;
        Sprite player[4];
        Sprite wall[4];
        Sprite tile;
        Sprite portal;
        std::vector<std::vector<Tile> > grid;
    public:
        Maze();

        void onStep();
        void onDraw(Graphics &g);

        void onUp();
        void onDown();
        void onRight();
        void onLeft();
};

#endif /* MAZE_H */
