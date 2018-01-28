#include "Room.h"

static bool intersects (const Room * const room, const uint16_t x, 
    const uint16_t y, const uint16_t w, const uint16_t h) 
{
    if (room->x + room->w < x || x + w < room->x)
        return false;

    if (room->y + room->h < y || y + h < room->y)
        return false;

    return true;
}

void Room_init (Room * const room, const uint16_t x, const uint16_t y, 
    const uint16_t w, const uint16_t h)
{
    room->x = x;
    room->y = y;
    room->w = w;
    room->h = h;

    room->intersects = &intersects;
}
