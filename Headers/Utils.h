#ifndef MAZER_UTILS_H
#define MAZER_UTILS_H

#include <stdlib.h>
#include <stdio.h>

/**
 * Prints out the given message as an error and exits, returning the given code.
 * 
 * @param message   The error message to print before exiting
 * @param code      The error code to return to the operating system 
 */
void throwError (const char *message, const int code);

#endif
