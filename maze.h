#ifndef MAZE_H
#define MAZE_H

#include "sprites.h"

#include <vector>

#define TILE_SIZE 50

struct Tile {
    bool up,left,down,right;
};

struct Enemy {
    int x,y;
};

struct Bomb {
    int x,y;
};

class Maze 
{// private:
        //dir is 0 = up, 1 = right, 2 = down, 3 = left
        int player_x,player_y,player_dir;
        int prev_player_x, prev_player_y;
        Sprite player[4];
        Sprite wall[4];
        Sprite tile;
        Sprite bomb;
        Sprite enemy_s;
        std::vector<std::vector<Tile> > grid;
        std::vector<Enemy> enemies;
        std::vector<Bomb> bombs;
        bool move;
        void blow_column(int x);
    public:
        Maze();

        void onStep();
        void onDraw(Graphics &g);

        void onUp();
        void onDown();
        void onRight();
        void onLeft();
        void onA();
};

#endif /* MAZE_H */
