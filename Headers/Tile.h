#ifndef MAZER_TILE_H
#define MAZER_TILE_H

#include <stdbool.h>
#include <stdlib.h>

#include <SDL2/SDL.h>

typedef struct _Tile
{
    bool valid;

    int16_t x, y, w, h;
    SDL_Color borderColor, fillColor;

    int16_t (*getX) (struct _Tile*);
    int16_t (*getY) (struct _Tile*);

    void (*destroy) (struct _Tile*);
    void (*getSize) (struct _Tile*, int16_t*, int16_t*);

    SDL_Color (*getBorderColor) (struct _Tile*);
    SDL_Color (*getFillColor) (struct _Tile*);
} Tile;

void Tile_init (Tile *tile);

#endif
