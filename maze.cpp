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
#define PORTAL_SPRITE "portal.png"

#include <cstdlib>

Maze::Maze() :
    player({Sprite(PLAYER_UP),Sprite(PLAYER_RIGHT),Sprite(PLAYER_DOWN),Sprite(PLAYER_LEFT)}),
    wall({Sprite(WALL_UP),Sprite(WALL_RIGHT),Sprite(WALL_DOWN),Sprite(WALL_LEFT)}),
    portal(PORTAL_SPRITE),
    tile(TILE_SPRITE) {
    for (int y = 0; y < MAZE_HEIGHT; ++y) {
        std::vector<Tile> row;
        for (int x = 0; x < MAZE_HEIGHT; ++x) {
            row.push_back({
                    !(y>0),
                    !(x>0)||rand()%2,
                    !(y<(MAZE_HEIGHT-1)),
                    !(x<(MAZE_WIDTH-1))});
        }
        grid.push_back(row);
    }

    player_x = 0; 
    player_y = 0;
    player_dir = 1;
}

void Maze::onStep() {
}

void Maze::onDraw(Graphics &g) {
    for (int y = 0; y < MAZE_HEIGHT; ++y) {
        for (int x = 0; x < MAZE_WIDTH; ++x) {
            int left = (x-player_x) * TILE_SIZE + 500;
            int top = (y-player_y) * TILE_SIZE + 350;
            tile.draw(g,left, top, TILE_SIZE,TILE_SIZE);
            if (grid[y][x].up) wall[0].draw(g,left,top,TILE_SIZE,TILE_SIZE);
            if (grid[y][x].down) wall[2].draw(g,left,top,TILE_SIZE,TILE_SIZE);
            if (grid[y][x].right) wall[1].draw(g,left,top,TILE_SIZE,TILE_SIZE);
            if (grid[y][x].left) wall[3].draw(g,left,top,TILE_SIZE,TILE_SIZE);
            if (x == player_x && y == player_y) player[0].draw(g,left,top,TILE_SIZE,TILE_SIZE);
        }
    }
    player[player_dir].draw(g,500,350,TILE_SIZE,TILE_SIZE);
    portal.draw(g,0,0,1050,750);
}

void Maze::onUp() {
    if (!grid[player_y][player_x].up) player_y--;
    player_dir = 0;
}

void Maze::onDown() {
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



