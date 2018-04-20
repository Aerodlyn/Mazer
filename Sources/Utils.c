#include "Utils.h"

#include <stdio.h>

void c_mapRGB (uint8_t *rgb, float *r, float *g, float *b) { mapRGB (rgb, *r, *g, *b); }

void mapRGB (uint8_t *rgb, float r, float g, float b)
{
    if (!rgb)
        rgb = malloc (sizeof (uint8_t) * r);
        
    rgb [0] = r * 255;
    rgb [1] = g * 255;
    rgb [2] = b * 255;
    rgb [3] = 255;
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
