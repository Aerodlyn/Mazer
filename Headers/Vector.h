#ifndef MAZER_VECTOR_H
#define MAZER_VECTOR_H

#include <stdbool.h>
#include <stdlib.h>

#include "Utils.h"

struct _Vector
{
    unsigned int capacity, size;
    void **data;
};
typedef struct _Vector Vector;

typedef void (*Vector_freeFunction) (void*);

bool Vector_isEmpty (const Vector * const vector);

bool Vector_isFull (const Vector * const vector);

void Vector_append (Vector * const vector, const void * const element);

/**
 * Frees dynamically created objects (allocated using malloc, calloc, etc.) that are stored within 
 *  the given Vector instance.
 * 
 * @param vector    The Vector instance to free
 * @param f         The function to use to free each object stored within this Vector instance
 *                      NOTE: Can be null, however no free call will be made on each object in the 
 *                              Vector instance.
 */
void Vector_free_d (Vector *vector, Vector_freeFunction f);

/**
 * Frees statically created objects (not allocated using malloc, calloc, etc.) that are stored 
 *  within the given Vector instance.
 * 
 * @param vector The Vector instance to free
 */
void Vector_free_s (Vector *vector);

/**
 * Returns the element at the given index of the given Vector instance.
 * 
 * @param vector    The Vector instance that contains the element to return
 * @param index     The index of the element to return
 * 
 * @return The element at the given index of the given Vector instace
 * 
 * NOTE: Throws an error and terminates the program if the given index is out of the Vector
 *          instance's range of elements.
 */
void* Vector_get (const Vector * const vector, const unsigned int index);

/**
 * Resizes the given Vector instance such that its capacity is equal to the given size.
 * 
 * @param vector    The Vector instance to resize
 * @param size      The new capacity of the Vector instance
 * 
 * NOTE: Throws an error and terminates the program if an attempt to resize the Vector instace
 *          below its number of elements is made.
 */
void Vector_resize (Vector * const vector, const unsigned int size);

/**
 * Removes the last element in the given Vector instance and frees it using the given function. Does
 *  nothing if the given Vector instance is empty.
 * 
 * @param vector    The Vector instance to remove the last element from
 * @param f         The function to use to free the last object stored within the given Vector 
 *                      instance; NOTE: Can be null, however no free call will be made on the 
 *                      last object in the Vector instance.
 */
void Vector_truncate_d (Vector * const vector, Vector_freeFunction f);

/**
 * Removes the last element in the given Vector instance.
 * 
 * @param vector The Vector instance to remove the last element from
 */
void Vector_truncate_s (Vector * const vector);

/**
 * Allocates and returns a new Vector instance with an initial capacity of 10.
 * 
 * @return A new and empty Vector instance
 */
Vector* Vector_new ();

#endif 
