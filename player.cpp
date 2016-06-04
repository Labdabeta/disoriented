#include "player.h"

#define PLAYER_UP "player_up.bmp"
#define PLAYER_RIGHT "player_right.bmp"
#define PLAYER_LEFT "player_left.bmp"
#define PLAYER_DOWN "player_down.bmp"

Player::Player() : imgs({Sprite(PLAYER_UP),Sprite(PLAYER_RIGHT),Sprite(PLAYER_DOWN),Sprite(PLAYER_LEFT)}) {
    dir = 1;
    x = 0;
    y = 0;
    move = false;
}

void Player::onStep() {
    if (move) {
        switch (dir) {
            case 0: y--; break;
            case 1: x++; break;
            case 2: y++; break;
            case 3: x--; break;
        }
        move = false;
    }
}

void Player::onDraw(Graphics &g, int tilesize) {
    imgs[dir].draw(g,512-tilesize/2,340-tilesize/2,tilesize,tilesize);
}

void Player::onUp() { dir = 0; move = true; }
void Player::onDown() { dir = 2; move = true; }
void Player::onRight() { dir = 1; move = true; }
void Player::onLeft() { dir = 3; move = true; }
