#include "maze.h"

#define MAZE_WIDTH 21
#define MAZE_HEIGHT 40

#define VIEWPORT_HEIGHT 5
#define VIEWPORT_WIDTH 5


#define WALL_UP "Wall_Up.png"
#define WALL_RIGHT "Wall_Right.png"
#define WALL_LEFT "Wall_Left.png"
#define WALL_DOWN "Wall_Down.png"
#define PLAYER_UP "player_up.png"
#define PLAYER_RIGHT "player_right.png"
#define PLAYER_LEFT "player_left.png"
#define PLAYER_DOWN "player_down.png"
#define TILE_SPRITE "tile.png"
#define ENEMY_SPRITE "enemy.png"
#define BOMB_SPRITE "player_left.png"

#include <cstdlib>
#include <time.h>

Maze::Maze() :
    player({Sprite(PLAYER_UP),Sprite(PLAYER_RIGHT),Sprite(PLAYER_DOWN),Sprite(PLAYER_LEFT)}),
    wall({Sprite(WALL_UP),Sprite(WALL_RIGHT),Sprite(WALL_DOWN),Sprite(WALL_LEFT)}),
    enemy_s(ENEMY_SPRITE),
    bomb(BOMB_SPRITE),
    tile(TILE_SPRITE) {
    srand(time(NULL));
    for (int y = 0; y < MAZE_HEIGHT; ++y) {
        std::vector<Tile> row;
        for (int x = 0; x < MAZE_HEIGHT; ++x) {
            row.push_back({
                    !(y>0)||rand()%2,
                    !(x>0),
                    !(y<(MAZE_HEIGHT-1)),
                    !(x<(MAZE_WIDTH-1))});
        }
        grid.push_back(row);
    }

    for (int y = 0; y < MAZE_HEIGHT; ++y) {
        int numwalls = rand() % 3;
        for (int w = 0; w < numwalls; ++w) {
            int wallind = rand() % (MAZE_WIDTH-1) + 1;
            grid[y][wallind].right = true;
            grid[y][wallind+1].left = true;
        }
    }

    player_x = 10; 
    player_y = 39;
    prev_player_x = 10;
    prev_player_y = 39;
    player_dir = 1;
}

void Maze::onStep() {
    for (int i=0; i < enemies.size(); ++i) {
        if (enemies[i].x == player_x && enemies[i].y == player_y) player_y++;
        if (rand() % 3 == 0) {
            enemies[i].y++;
            for (int ii=0; ii < enemies.size(); ++ii) {
                if (i != ii && enemies[ii].x == enemies[i].x && enemies[ii].y == enemies[i].y)
                    enemies[i].y--;
            }
            if (enemies[i].y > MAZE_HEIGHT) enemies.erase(enemies.begin() + i);
        }
        if (enemies[i].x == player_x && enemies[i].y == player_y) {
            player_dir = 2;
            if (player_y >= MAZE_HEIGHT - 1) { enemies.erase(enemies.begin() + 1); }
            else if (!grid[player_y][player_x].down) { player_y++; }
            else { enemies.erase(enemies.begin() + 1); }
        }
        for (int b=0; b < bombs.size(); ++b) {
            if (bombs[b].x == enemies[i].x && bombs[b].y == enemies[i].y) {
                blow_column(bombs[b].x);
                bombs.erase(bombs.begin()+b);
                break;
            }
        }
    }
    enemies.push_back({rand()%MAZE_WIDTH, 0});
}

void Maze::onDraw(Graphics &g) {
    for (int y = 0; y < MAZE_HEIGHT; ++y) {
        for (int x = 0; x < MAZE_WIDTH; ++x) {
            int left = x * TILE_SIZE;//(x-((prev_player_x+player_x)/2.0)) * TILE_SIZE + 500;
            int top = (y-player_y) * TILE_SIZE + 350;
            tile.draw(g,left, top, TILE_SIZE,TILE_SIZE);
            if (grid[y][x].up) wall[0].draw(g,left,top,TILE_SIZE,TILE_SIZE);
            if (grid[y][x].down) wall[2].draw(g,left,top,TILE_SIZE,TILE_SIZE);
            if (grid[y][x].right) wall[1].draw(g,left,top,TILE_SIZE,TILE_SIZE);
            if (grid[y][x].left) wall[3].draw(g,left,top,TILE_SIZE,TILE_SIZE);
        }
    }

    for (auto &enemy : enemies) {
        enemy_s.draw(g,enemy.x*TILE_SIZE,
                       (enemy.y-player_y) * TILE_SIZE + 350,
                       TILE_SIZE, TILE_SIZE);
    }

    for (auto &b : bombs) {
        bomb.draw(g,b.x*TILE_SIZE,
                    (b.y-player_y) * TILE_SIZE +350,
                    TILE_SIZE, TILE_SIZE);
    }
    player[player_dir].draw(g,player_x*TILE_SIZE,350,TILE_SIZE,TILE_SIZE);
    prev_player_x = player_x;
    prev_player_y = player_y;
}

void Maze::onUp() {
    if (!grid[player_y][player_x].up) player_y--;
    player_dir = 0;
}

void Maze::onDown() {
    if (player_y >= MAZE_HEIGHT - 1) { player_dir = 2; return; }
    if (!grid[player_y][player_x].down) player_y++;
    player_dir = 2;
}

void Maze::onRight() {
    if (!grid[player_y][player_x].right) player_x++;
    player_dir = 1;
}

void Maze::onLeft() {
    if (!grid[player_y][player_x].left) player_x--;
    player_dir = 3;
}

void Maze::onA() {
    bombs.push_back({player_x,player_y});
}

void Maze::blow_column(int x) {
    for (auto i = enemies.begin(); i != enemies.end(); ++i) {
        if (i->x == x) { enemies.erase(i); blow_column(x); return; }
    }
}
