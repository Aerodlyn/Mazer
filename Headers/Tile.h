#ifndef MAZER_TILE_H
#define MAZER_TILE_H

#include <allegro5/allegro.h>

#include <stdbool.h>
#include <stdlib.h>

typedef struct _Tile
{
    bool valid;

    int16_t x, y, size;

    ALLEGRO_COLOR borderColor, fillColor;

    int16_t (*getSize) (struct _Tile*);
    int16_t (*getX) (struct _Tile*);
    int16_t (*getY) (struct _Tile*);

    void (*destroy) (struct _Tile*);

    ALLEGRO_COLOR (*getBorderColor) (struct _Tile*);
    ALLEGRO_COLOR (*getFillColor) (struct _Tile*);
} Tile;

void Tile_init (Tile *tile, int16_t x, int16_t y, int16_t size, ALLEGRO_COLOR border, 
    ALLEGRO_COLOR fill);

#endif
