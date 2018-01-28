#include "Tile.h"

#include <stdio.h>

static unsigned int getSize (Tile *tile) { return tile->size; }

static unsigned int getX (Tile *tile) { return tile->x; }

static unsigned int getY (Tile *tile) { return tile->y; }

static ALLEGRO_COLOR getBorderColor (Tile *tile) { return tile->borderColor; }

static ALLEGRO_COLOR getFillColor (Tile *tile) { return tile->fillColor; }

void Tile_init (Tile *tile, unsigned int x, unsigned int y, unsigned int size, ALLEGRO_COLOR border, ALLEGRO_COLOR fill)
{
    tile->x = x;
    tile->y = y;
    tile->size = size;
    tile->borderColor = border;
    tile->fillColor = fill;

    tile->getX = &getX;
    tile->getY = &getY;
    tile->getSize = &getSize;
    tile->getBorderColor = &getBorderColor;
    tile->getFillColor = &getFillColor;
}
