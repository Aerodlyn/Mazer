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

static SDL_Color getBorderColor (Tile *tile) { return tile->borderColor; }

static SDL_Color getFillColor (Tile *tile) { return tile->fillColor; }

void Tile_init (Tile *tile)
{
    tile->borderColor.r = 255;
    tile->borderColor.g = 255;
    tile->borderColor.b = 255;
    tile->borderColor.a = 255;

    tile->fillColor.r = 255;
    tile->fillColor.g = 0;
    tile->fillColor.b = 0;
    tile->fillColor.a = 0;

    tile->valid = true;

    tile->getX = &getX;
    tile->getY = &getY;
    tile->getSize = &getSize;
    tile->getBorderColor = &getBorderColor;
    tile->getFillColor = &getFillColor;

    tile->destroy = &destroy;
}
