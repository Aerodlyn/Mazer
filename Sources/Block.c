#include "Block.h"

Block *Block_create (unsigned int x, unsigned int y, ALLEGRO_COLOR color) 
{
    Block *block = calloc (1, sizeof (struct _Block));

    block->x        = x;
    block->y        = y;
    block->color    = color;

    return block;
}

unsigned int Block_getX (const Block * const block) { return block->x; }

unsigned int Block_getY (const Block * const block) { return block->y; }

void Block_free (Block *block) 
{ 
    free (block); 
    block = NULL;
}

ALLEGRO_COLOR Block_getColor (const Block * const block) { return block->color; }
