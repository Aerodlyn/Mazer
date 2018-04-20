#include "Tile.h"
#include <stdio.h>

static int16_t getX (Tile *tile) { return tile->x; }

static int16_t getY (Tile *tile) { return tile->y; }

static void destroy (Tile *tile)
{
    free ((void*) tile);
    tile = NULL;
}

static void getSize (Tile *tile, int16_t *w, int16_t *h)
{
    *w = tile->w;
    *h = tile->h;
}

static uint8_t* getBorderColor (Tile *tile) { return tile->borderColor; }

static uint8_t* getFillColor (Tile *tile) { return tile->fillColor; }

void c_Tile_init (Tile *tile, int16_t *x, int16_t *y, int16_t *w, int16_t *h) { Tile_init (tile, *x, *y, *w, *h, NULL, NULL); }

void Tile_init (Tile *tile, int16_t x, int16_t y, int16_t w, int16_t h, uint8_t *border, uint8_t *fill)
{
    tile->x = x;
    tile->y = y;
    tile->w = w;
    tile->h = h;
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
