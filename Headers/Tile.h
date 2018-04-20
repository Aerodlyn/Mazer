#ifndef MAZER_TILE_H
#define MAZER_TILE_H

#include <stdbool.h>
#include <stdlib.h>

typedef struct _Tile
{
    bool valid;

    int16_t x, y, w, h;
    uint8_t *borderColor, *fillColor;

    int16_t (*getX) (struct _Tile*);
    int16_t (*getY) (struct _Tile*);

    void (*destroy) (struct _Tile*);
    void (*getSize) (struct _Tile*, int16_t*, int16_t*);

    uint8_t* (*getBorderColor) (struct _Tile*);
    uint8_t* (*getFillColor) (struct _Tile*);
} Tile;

void c_Tile_init (Tile *tile, int16_t *x, int16_t *y, int16_t *w, int16_t *h);
void Tile_init (Tile *tile, int16_t x, int16_t y, int16_t w, int16_t h, uint8_t *border, uint8_t *fill);

#endif
