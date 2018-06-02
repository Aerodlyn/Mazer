#ifndef MAZER_TILE_H
#define MAZER_TILE_H

#include <stdbool.h>

// https://wiki.libsdl.org/FrontPage
#include <SDL2/SDL.h>

typedef enum _Tile_Borders
{
    BOTTOM  = 1,
    LEFT    = 2,
    RIGHT   = 4,
    TOP     = 8
} Tile_Borders;

typedef struct _Tile
{
    bool valid;
    uint8_t borders;

    SDL_Color borderColor, fillColor;

    SDL_Color (*getBorderColor) (struct _Tile*);
    SDL_Color (*getFillColor) (struct _Tile*);
} Tile;

void Tile_init (Tile *tile);

void Tile_setBorders (Tile * const tile, const Tile_Borders borders);

uint8_t Tile_getTileBorders (const Tile * const tile);

#endif
