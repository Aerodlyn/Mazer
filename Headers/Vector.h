#ifndef MAZER_VECTOR_H
#define MAZER_VECTOR_H

#include <stdbool.h>
#include <stdlib.h>

struct _Vector
{
    unsigned int capacity, size;
    void **data;
};
typedef struct _Vector Vector;

typedef void (*Vector_freeFunction) (void*);

bool Vector_isFull (const Vector * const vector);

void Vector_append (Vector *vector, void *element);

/**
 * Frees dynamically created objects (allocated using malloc, calloc, etc.) that are stored within 
 *  this Vector instance.
 * 
 * @param vector    The Vector instance to free
 * @param f         The function to use to free each object stored within this Vector instance
 *                      NOTE: Can be null, however no free call will be made on each object in the 
 *                              Vector instance.
 */
void Vector_free_d (Vector *vector, Vector_freeFunction f);

/**
 * Frees statically created objects (not allocated using malloc, calloc, etc.) that are stored 
 *  within this Vector instance.
 * 
 * @param vector The Vector instance to free
 */
void Vector_free_s (Vector *vector);

void *Vector_get (Vector *vector, unsigned int index);

void Vector_resize (Vector * const vector, unsigned int size);

Vector *Vector_new ();

#endif 
