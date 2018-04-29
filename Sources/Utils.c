#include "Utils.h"

void c_mapRGB (Tile *tile, float *r, float *g, float *b) { mapRGB (tile, *r, *g, *b); }

void mapRGB (Tile *tile, float r, float g, float b)
{
    tile->fillColor.r = r * 255;
    tile->fillColor.g = g * 255;
    tile->fillColor.b = b * 255;
    tile->fillColor.a = 255;

    // printf ("%d, %d, %d, %d\n", tile->fillColor.r, tile->fillColor.g, tile->fillColor.b, tile->fillColor.a);
}

/**
 * Prints out the given message as an error and exits, returning the given code.
 * 
 * @param message   The error message to print before exiting
 * @param code      The error code to return to the operating system 
 */
void throwError (const char *message, const int code)
{
    fprintf (stderr, "ERROR: %s\n", message);
    exit (code);
}
