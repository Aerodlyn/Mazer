#ifndef MAZER_ROOM_H
#define MAZER_ROOM_H

#include <stdbool.h>
#include <stdint.h>

typedef struct _Room
{
    bool valid;

    int16_t w, h, x, y;

    bool (*intersects) (const struct _Room * const, const int16_t, 
        const int16_t, const int16_t, const int16_t);
} Room;

void Room_init (Room * const room, const int16_t x, const int16_t y, 
    const int16_t w, const int16_t h);

#endif
