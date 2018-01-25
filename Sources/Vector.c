#include "Vector.h"

bool Vector_isEmpty (const Vector * const vector) { return vector->size == 0; }

bool Vector_isFull (const Vector * const vector) { return vector->size >= vector->capacity; }

void Vector_append (Vector * const vector, const void * const element)
{
    if (Vector_isFull (vector))
        Vector_resize (vector, vector->capacity * 2);

    vector->data [vector->size++] = element;
}

/**
 * Frees dynamically created objects (allocated using malloc, calloc, etc.) that are stored within 
 *  this Vector instance.
 * 
 * @param vector    The Vector instance to free
 * @param f         The function to use to free each object stored within this Vector instance
 *                      NOTE: Can be null, however no free call will be made on each object in the 
 *                              Vector instance.
 */
void Vector_free_d (Vector *vector, Vector_freeFunction f)
{
    if (f)
    {
        for (unsigned int i = 0; i < vector->size; i++)
            f (vector->data [i]);
    }

    free (vector->data);
    free (vector);

    vector = NULL;
}

/**
 * Frees statically created objects (not allocated using malloc, calloc, etc.) that are stored 
 *  within this Vector instance.
 * 
 * @param vector The Vector instance to free
 */
void Vector_free_s (Vector *vector) { Vector_free_d (vector, NULL); }

void* Vector_get (const Vector * const vector, const unsigned int index)
{
    if (index >= vector->size)
        throwError ("Cannot access elements outside of Vector instance's size.", -1);

    return vector->data [index];
}

void Vector_resize (Vector * const vector, const unsigned int size)
{
    if (size < vector->size)
        throwError ("Cannot resize Vector instance to below its current size.", -1);

    vector->capacity    = size;
    vector->data        = realloc (vector->data, vector->capacity);
}

void Vector_truncate_d (Vector * const vector, Vector_freeFunction f)
{
    if (Vector_isEmpty (vector))
        throwError ("Cannot truncate from an empty Vector instance.", -1);

    if (f)
        f (vector->data [--vector->size]);

    else
        vector->size--;
}

void Vector_truncate_s (Vector * const vector) { Vector_truncate_d (vector, NULL); }

Vector *Vector_new ()
{
    Vector *vector = calloc (1, sizeof (struct _Vector));

    vector->size        = 0;
    vector->capacity    = 10;
    vector->data        = calloc (vector->capacity, sizeof (void*));

    return vector;
}
