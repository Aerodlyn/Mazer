#ifndef MAZER_TILE_H
#define MAZER_TILE_H

#include <allegro5/allegro.h>

#include <stdlib.h>

typedef struct _Tile
{
    unsigned int x, y;
    unsigned int size;

    ALLEGRO_COLOR color;

    unsigned int (*getSize) (struct _Tile*);
    unsigned int (*getX) (struct _Tile*);
    unsigned int (*getY) (struct _Tile*);

    void (*destroy) (void*);

    ALLEGRO_COLOR (*getColor) (struct _Tile*);
} Tile;

Tile* Tile_create (unsigned int x, unsigned int y, unsigned int size, ALLEGRO_COLOR color);

#endif
