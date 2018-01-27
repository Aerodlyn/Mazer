#ifndef MAZER_VECTOR_H
#define MAZER_VECTOR_H

#define Vector_base                     \
    struct { size_t capacity, size; }

#define Vector(T)               \
    struct Vector_##T           \
    {                           \
        Vector_base;            \
        T *data;                \
    }

#define Vector_at(V, I) (&V->data [I])

#define Vector_create(T)                                                    \
({                                                                          \
    struct Vector_##T *v = malloc (sizeof (Vector (T)));                    \
                                                                            \
    v->capacity = 10;                                                       \
    v->size = 0;                                                            \
                                                                            \
    v->data = malloc (sizeof (T) * v->capacity);                            \
    v;                                                                      \
})

#define Vector_destroy(V)   \
({                          \
    free (V->data);         \
    free (V);               \
                            \
    V = NULL;               \
})

#define Vector_push(V, E)                                                           \
({                                                                                  \
    if (V->size >= V->capacity)                                                     \
    {                                                                               \
        V->capacity *= 2;                                                           \
        V->data = realloc (V->data, sizeof (*V->data) * V->capacity);               \
    }                                                                               \
                                                                                    \
    V->data [V->size++] = *E;                                                       \
})

#define Vector_size(V) (V->size)

#endif
