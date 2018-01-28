#ifndef MAZER_ROOM_H
#define MAZER_ROOM_H

#include <stdbool.h>
#include <stdint.h>

typedef struct _Room
{
    unsigned int w, h;
    unsigned int x, y;

    bool (*intersects) (const struct _Room * const, const uint16_t, 
        const uint16_t, const uint16_t, const uint16_t);
} Room;

void Room_init (Room * const room, const uint16_t x, const uint16_t y, 
    const uint16_t w, const uint16_t h);

#endif
