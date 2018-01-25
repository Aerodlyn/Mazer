#include "Vector.h"

/**
 * Returns whether or not the given Vector instance is empty.
 * 
 * @param vector The Vector instance to check
 * 
 * @return True if the given Vector instance is empty, false otherwise
 */
bool Vector_isEmpty (const Vector * const vector) { return vector->size == 0; }

/**
 * Returns whether or not the given Vector instance is full, and may need to be resized.
 * 
 * @param vector The Vector instance to check
 * 
 * @return True if the given Vector instance is full, false otherwise
 */
bool Vector_isFull (const Vector * const vector) { return vector->size >= vector->capacity; }

/**
 * Appends the given element to the end of the given Vector instance, growing the Vector instance
 *  if needed.
 * 
 * @param vector    The Vector instance to append the given element to
 * @param element   The element to add to the given Vector instance
 */
void Vector_append (Vector * const vector, const void * const element)
{
    if (Vector_isFull (vector))
        Vector_resize (vector, vector->capacity * 2);

    vector->data [vector->size++] = element;
}

/**
 * Frees dynamically created objects (allocated using malloc, calloc, etc.) that are stored within 
 *  the given Vector instance.
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
 *  within the given Vector instance.
 * 
 * @param vector The Vector instance to free
 */
void Vector_free_s (Vector *vector) { Vector_free_d (vector, NULL); }

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
void* Vector_get (const Vector * const vector, const unsigned int index)
{
    if (index >= vector->size)
        throwError ("Cannot access elements outside of Vector instance's size.", -1);

    return vector->data [index];
}

/**
 * Inserts the given element to the given Vector instance at the given index, growing the Vector
 *  instance if needed.
 * 
 * @param vector    The Vector instance to insert the given element into
 * @param element   The element to insert into the Vector instance
 * @param index     The index of where the element should be inserted at
 * 
 * NOTE: Throws an error and terminates the program if the given index is out of the Vector
 *          instance's range of elements.
 */
void Vector_insert (Vector * const vector, const void * const element, const unsigned int index)
{
    if (index >= vector->size)
        throwError ("Cannot add elements outside of Vector instance's range.", -1);

    if (Vector_isFull (vector))
        Vector_resize (vector, vector->capacity * 2);

    for (int i = vector->size; i > index; i--)
        vector->data [i] = vector->data [i - 1];

    vector->data [index] = element;
    vector->size++;
}

/**
 * Removes the element that is located within the given Vector instance at the given index and
 *  frees it using the given function. Does nothing if the Vector instance is empty.
 * 
 * @param vector    The Vector instance that contains the element to remove and free
 * @param index     The index of the element to remove and free
 * @param f         The function to use to free the object stored within the given Vector
 *                      instance at the given index; NOTE: Can be null, however no free call will 
 *                      be made on the last object in the Vector instance.
 */
void Vector_remove (Vector * const vector, const unsigned int index, Vector_freeFunction f)
{
    if (index >= vector->size)
        throwError ("Cannot remove an element that is outside of the Vector's instances range.", -1);

    if (Vector_isEmpty (vector))
        return;

    if (f)
        f (vector->data [index]);

    for (unsigned int i = index; i < vector->size; i++)
        vector->data [i] = vector->data [i + 1];

    vector->size--;
}

/**
 * Resizes the given Vector instance such that its capacity is equal to the given size.
 * 
 * @param vector    The Vector instance to resize
 * @param size      The new capacity of the Vector instance
 * 
 * NOTE: Throws an error and terminates the program if an attempt to resize the Vector instace
 *          below its number of elements is made.
 */
void Vector_resize (Vector * const vector, const unsigned int size)
{
    if (size < vector->size)
        throwError ("Cannot resize Vector instance to below its current size.", -1);

    vector->capacity    = size;
    vector->data        = realloc (vector->data, vector->capacity);
}

/**
 * Removes the last element in the given Vector instance and frees it using the given function. Does
 *  nothing if the given Vector instance is empty.
 * 
 * @param vector    The Vector instance to remove the last element from
 * @param f         The function to use to free the last object stored within the given Vector 
 *                      instance; NOTE: Can be null, however no free call will be made on the 
 *                      last object in the Vector instance.
 */
void Vector_truncate_d (Vector * const vector, Vector_freeFunction f)
{
    if (Vector_isEmpty (vector))
        return;

    if (f)
        f (vector->data [--vector->size]);

    else
        vector->size--;
}

/**
 * Removes the last element in the given Vector instance.
 * 
 * @param vector The Vector instance to remove the last element from
 */
void Vector_truncate_s (Vector * const vector) { Vector_truncate_d (vector, NULL); }

/**
 * Allocates and returns a new Vector instance with an initial capacity of 10.
 * 
 * @return A new and empty Vector instance
 */
Vector* Vector_new ()
{
    Vector *vector = calloc (1, sizeof (struct _Vector));

    vector->size        = 0;
    vector->capacity    = 10;
    vector->data        = calloc (vector->capacity, sizeof (void*));

    return vector;
}
