#ifndef MAZER_BLOCK_H
#define MAZER_BLOCK_H

#include <allegro5/allegro.h>

#include <stdlib.h>

struct _Block
{
    unsigned int x, y;
    unsigned int size;

    ALLEGRO_COLOR color;
};
typedef struct _Block Block;

Block *Block_create (unsigned int x, unsigned int y, ALLEGRO_COLOR color);

unsigned int Block_getX (const Block * const block);

unsigned int Block_getY (const Block * const block);

void Block_free (Block *block);

ALLEGRO_COLOR Block_getColor (const Block * const block);

#endif
