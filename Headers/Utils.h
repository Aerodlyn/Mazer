#ifndef MAZER_UTILS_H
#define MAZER_UTILS_H

#include <stdlib.h>
#include <stdio.h>

void c_mapRGB (uint8_t *rgb, float *r, float *g, float *b);

void mapRGB (uint8_t *rgb, float r, float g, float b);

/**
 * Prints out the given message as an error and exits, returning the given code.
 * 
 * @param message   The error message to print before exiting
 * @param code      The error code to return to the operating system 
 */
void throwError (const char *message, const int code);

#endif
