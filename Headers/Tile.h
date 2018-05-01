#ifndef MAZER_TILE_H
#define MAZER_TILE_H

#include <stdbool.h>

// https://wiki.libsdl.org/FrontPage
#include <SDL2/SDL.h>

typedef struct _Tile
{
    bool valid;

    SDL_Color borderColor, fillColor;

    SDL_Color (*getBorderColor) (struct _Tile*);
    SDL_Color (*getFillColor) (struct _Tile*);
} Tile;

void Tile_init (Tile *tile);

#endif
