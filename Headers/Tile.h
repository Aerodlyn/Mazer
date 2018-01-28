#ifndef MAZER_TILE_H
#define MAZER_TILE_H

#include <allegro5/allegro.h>

#include <stdlib.h>

typedef struct _Tile
{
    unsigned int x, y;
    unsigned int size;

    ALLEGRO_COLOR borderColor, fillColor;

    unsigned int (*getSize) (struct _Tile*);
    unsigned int (*getX) (struct _Tile*);
    unsigned int (*getY) (struct _Tile*);

    void (*destroy) (void*);

    ALLEGRO_COLOR (*getBorderColor) (struct _Tile*);
    ALLEGRO_COLOR (*getFillColor) (struct _Tile*);
} Tile;

void Tile_init (Tile *tile, unsigned int x, unsigned int y, unsigned int size, ALLEGRO_COLOR border, ALLEGRO_COLOR fill);

#endif
