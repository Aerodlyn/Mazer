#include "Vector.h"

bool Vector_isFull (const Vector * const vector) { return vector->size >= vector->capacity; }

void Vector_append (Vector *vector, void *element)
{
    if (Vector_isFull (vector))
    {
        vector->capacity *= 2;
        vector->data = realloc (vector->data, vector->capacity);
    }

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

void *Vector_get (Vector *vector, unsigned int index)
{
    return vector->data [index];
}

Vector *Vector_new ()
{
    Vector *vector = calloc (1, sizeof (struct _Vector));

    vector->size = 0;
    vector->capacity = 10;
    vector->data = calloc (vector->capacity, sizeof (void*));

    return vector;
}
