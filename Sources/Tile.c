#include "Tile.h"
#include <stdio.h>

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

    tile->getBorderColor = &getBorderColor;
    tile->getFillColor = &getFillColor;
}

void Tile_setBorders (Tile * const tile, const Tile_Borders borders) { tile->borders = borders; }

uint8_t Tile_getTileBorders (const Tile * const tile) { return tile->borders; }
