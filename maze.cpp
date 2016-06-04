#include "maze.h"

#define MAZE_WIDTH 40
#define MAZE_HEIGHT 40

#define VIEWPORT_HEIGHT 5
#define VIEWPORT_WIDTH 5


#define WALL_UP "wall_up.png"
#define WALL_RIGHT "wall_right.png"
#define WALL_LEFT "wall_left.png"
#define WALL_DOWN "wall_down.png"
#define PLAYER_UP "player_up.png"
#define PLAYER_RIGHT "player_right.png"
#define PLAYER_LEFT "player_left.png"
#define PLAYER_DOWN "player_down.png"
#define TILE_SPRITE "tile.png"
#define ENEMY_SPRITE "enemy.png"

#include <cstdlib>
#include <time.h>

Maze::Maze() :
    player({Sprite(PLAYER_UP),Sprite(PLAYER_RIGHT),Sprite(PLAYER_DOWN),Sprite(PLAYER_LEFT)}),
    wall({Sprite(WALL_UP),Sprite(WALL_RIGHT),Sprite(WALL_DOWN),Sprite(WALL_LEFT)}),
    enemy_s(ENEMY_SPRITE),
    tile(TILE_SPRITE) {
    srand(time(NULL));
    for (int y = 0; y < MAZE_HEIGHT; ++y) {
        std::vector<Tile> row;
        for (int x = 0; x < MAZE_HEIGHT; ++x) {
            row.push_back({
                    !(y>0)||rand()%2||rand()%2,
                    !(x>0),
                    !(y<(MAZE_HEIGHT-1)),
                    !(x<(MAZE_WIDTH-1))});
        }
        grid.push_back(row);
    }

    player_x = 20; 
    player_y = 39;
    prev_player_x = 20;
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
            onDown();
        }
    }
    enemies.push_back({rand()%MAZE_WIDTH, 0});
    enemies.push_back({rand()%MAZE_WIDTH, 0});
    enemies.push_back({rand()%MAZE_WIDTH, 0});
}

void Maze::onDraw(Graphics &g) {
    for (int y = 0; y < MAZE_HEIGHT; ++y) {
        for (int x = 0; x < MAZE_WIDTH; ++x) {
            int left = (x-((prev_player_x+player_x)/2.0)) * TILE_SIZE + 500;
            int top = (y-((prev_player_y+player_y)/2.0)) * TILE_SIZE + 350;
            tile.draw(g,left, top, TILE_SIZE,TILE_SIZE);
            if (grid[y][x].up) wall[0].draw(g,left,top,TILE_SIZE,TILE_SIZE);
            if (grid[y][x].down) wall[2].draw(g,left,top,TILE_SIZE,TILE_SIZE);
            if (grid[y][x].right) wall[1].draw(g,left,top,TILE_SIZE,TILE_SIZE);
            if (grid[y][x].left) wall[3].draw(g,left,top,TILE_SIZE,TILE_SIZE);
        }
    }
    player[player_dir].draw(g,500,350,TILE_SIZE,TILE_SIZE);

    for (auto &enemy : enemies) {
        enemy_s.draw(g,(enemy.x - ((prev_player_x + player_x)/2.0)) * TILE_SIZE + 500,
                       (enemy.y - ((prev_player_y + player_y)/2.0)) * TILE_SIZE + 350,
                       TILE_SIZE, TILE_SIZE);
    }
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



