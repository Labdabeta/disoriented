#ifndef MAZE_H
#define MAZE_H

#define SCARY_ENEMY_PROB 100

#include "sprites.h"

#include <vector>

struct Tile {
    bool up,left,down,right;
    bool revealed;
};

class Enemy {
    public:
        int x,y;
        int dir;
        int type; // 0 = normal, 1 = wall, 2 = spider
        Enemy(int xDim, int yDim){
            type = 0;
            if (rand()%SCARY_ENEMY_PROB == 0) {
                type = rand() % 2 + 1;
            }
            dir = rand()%4;
            switch (dir) {
            case 0:{ // enemy goes up, spawn at the bottom of the maze 
                       y = yDim + 1;
                       x = rand()%xDim;
                       break;
                   }
            case 2:{ // enemy goes down, spawn at the top of the maze 
                       y = -1;
                       x = rand()%xDim;
                       break;
                   }
            case 1:{ // enemy goes right, spawn at the left of the maze 
                       y = rand()%yDim;
                       x = -1;
                       break;
                   }
            case 3:{ // enemy goes left, spawn at the right of the maze 
                       y = rand()%yDim;
                       x = xDim + 1;
                       break;	
                   }
            }
        }       
        void move() { 
            switch (dir) {
                case 0: y--; break;
                case 1: x++; break;
                case 2: y++; break;
                case 3: x--; break;
            }
        }
        void unmove() {
            switch (dir) {
                case 0: y++; break;
                case 1: x--; break;
                case 2: y--; break;
                case 3: x++; break;
            }
        }
};

struct Bomb {
    int x,y;
};

struct Orb {
    int x,y;
};

struct Coord {
    int x,y;
};

class Maze 
{// private:
        //dir is 0 = up, 1 = right, 2 = down, 3 = left
        int player_x,player_y,player_dir;
        int prev_player_x, prev_player_y;
        Sprite player[4]; Sprite key_player[4]; Sprite wall_s[4];
        Sprite fplayer[4]; Sprite fkey_player[4]; 
        Sprite tile[7]; Sprite bomb; Sprite dynamite;
        Sprite upfire; Sprite downfire; Sprite leftfire;
        Sprite rightfire; Sprite midfire; Sprite horfire;
        Sprite enemy_s[4]; Sprite portal[3]; Sprite orb_s;
        Sprite key; Sprite exit; Sprite torch_s;
        Sprite tileh[7]; Sprite ammo_s; Sprite wenemy_s[4];
        Sprite web; Sprite webenemy_s[4];
        Sprite webbed[5];
        std::vector<std::vector<Tile> > grid;
        std::vector<Enemy> enemies;
        std::vector<Bomb> bombs;
        std::vector<Bomb> dynamites;
        bool move;
        void blow_column(int x);
        void blow_row(int y);
        bool are_opposite(int a, int b);
        Orb orb;
        std::vector<int> blown_columns;
        std::vector<int> blown_rows;
        std::vector<Coord> webs;
        Coord torch;
        int game_over;
        int getX(int x);
        int getY(int y);
        int health;
        Coord key_or_exit;
        bool has_key;
        bool win; 
        int ammo;
        int MAZE_HEIGHT;
        int MAZE_WIDTH;
        int MAZE_DENSITY;
        int enemycount;
        int level;
        int stucktime;
        void collision_check();
        bool ismale;
    public:
        Maze(int w, int h, float d, int e, int l);
        void reset(int w, int h, float d, int e, int l);

        void onStep();
        void onDraw(Graphics &g);

        void onUp();
        void onDown();
        void onRight();
        void onLeft();
        void onA();
        void onB();

        // returns enemy type + 1, or 0 if alive (-1 for mrhuggz)
        int dead() { return game_over; }
        bool winner() { return win; }

        void male(bool male) { ismale = male; }
};

#endif /* MAZE_H */
