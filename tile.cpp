#include "tile.h"

#define TILE_SPRITE "tile.bmp"

Sprite *Tile::tile = NULL;

Tile::Tile(bool up, bool left, bool down, bool right, int x, int y)
    : up(up), left(left), down(down), right(right) {
    if (tile == NULL) {
        tile = new Sprite(TILE_SPRITE);
    }
}

void Tile::draw(Graphics &g, int px, int py, int tsize) {
    if (!tile) return;
    tile->draw(g,(x-px)*tsize,(y-py)*tsize,tsize,tsize);
}
