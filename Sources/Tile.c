#include "Tile.h"

#include <stdio.h>

static int16_t getSize (Tile *tile) { return tile->size; }

static int16_t getX (Tile *tile) { return tile->x; }

static int16_t getY (Tile *tile) { return tile->y; }

static void destroy (Tile *tile)
{
    free ((void*) tile);
    tile = NULL;
}

static ALLEGRO_COLOR getBorderColor (Tile *tile) { return tile->borderColor; }

static ALLEGRO_COLOR getFillColor (Tile *tile) { return tile->fillColor; }

void Tile_init (Tile *tile, int16_t x, int16_t y, int16_t size, ALLEGRO_COLOR border, 
    ALLEGRO_COLOR fill)
{
    tile->x = x;
    tile->y = y;
    tile->size = size;
    tile->borderColor = border;
    tile->fillColor = fill;
    tile->valid = true;

    tile->getX = &getX;
    tile->getY = &getY;
    tile->getSize = &getSize;
    tile->getBorderColor = &getBorderColor;
    tile->getFillColor = &getFillColor;

    tile->destroy = &destroy;
}
