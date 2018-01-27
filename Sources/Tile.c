#include "Tile.h"

#include <stdio.h>

static unsigned int getSize (Tile *tile) { return tile->size; }

static unsigned int getX (Tile *tile) { return tile->x; }

static unsigned int getY (Tile *tile) { return tile->y; }

static ALLEGRO_COLOR getColor (Tile *tile) { return tile->color; }

Tile* Tile_create (unsigned int x, unsigned int y, unsigned int size, ALLEGRO_COLOR color)
{
    Tile *tile = malloc (sizeof (struct _Tile));

    tile->x = x;
    tile->y = y;
    tile->size = size;
    tile->color = color;

    tile->getX = &getX;
    tile->getY = &getY;
    tile->getSize = &getSize;
    tile->getColor = &getColor;
    tile->destroy = &free;

    return tile;
}
