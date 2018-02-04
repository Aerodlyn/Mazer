#include "Application.h"

int main (int argc, char **argv)
{
    if (!init ())
    {
        throwError ("Required Allegro components failed to initialize.", -1);
        return -1;
    }

    while (running)
    {
        input ();
        update ();
        render ();
    }

    destroy ();

    return 0;
}

/**
 * Attempts to inititalize required Allegro objects.
 *
 * @return Returns false if any Allegro object was unable to be created, true
 *          otherwise
 */
bool init ()
{
    if (!al_init ())
        return false;

    display = al_create_display (450, 450);

    if (!display)
        return false;

    eventQueue = al_create_event_queue ();

    if (!eventQueue)
    {
        destroy ();
        return false;
    }

    al_register_event_source (eventQueue,
        al_get_display_event_source (display));

    generate ();

    return true;
}

void destroy ()
{
    if (display)
        al_destroy_display (display);

    if (eventQueue)
        al_destroy_event_queue (eventQueue);

    if (tiles)
        Vector_destroy (tiles);
}

void generate ()
{
    srand (time (NULL));

    tiles = Vector_create (Tile);

    generateRooms ();
}

void generateRooms ()
{
    int attempts = 25, minSize = 5, padding = 1;
    int rooms [attempts * 4];

    generate_rooms (rooms, &attempts, &minSize, &NUM_OF_TILES_PER_SIDE, &padding);

    for (int i = 0; i < attempts; i++)
    {
        int x = rooms [i * 4], y = rooms [i * 4 + 1];
        int w = rooms [i * 4 + 2], h = rooms [i * 4 + 3];

        // Don't add room if it overlaps another
        if (x == -1)
            continue;

        uint16_t xc = 0, yc = 0;
        for (uint16_t j = 0; j < w * h; j++)
        {
            Tile tile;
            Tile_init (&tile, x * getTileWidth () + xc * getTileWidth (),
                y * getTileWidth () + yc * getTileWidth (), getTileWidth (),
                BLOCK_BORDER, BLOCK_FILL);

            test_tile (&tile);

            Vector_push (tiles, tile);

            xc++;
            if (xc >= w)
            {
                xc = 0;
                yc++;
            }
        }
    }

    /*Vector (Room) *rooms = Vector_create (Room);

    for (uint8_t i = 0; i < ROOM_ATTEMPTS; i++)
    {
        uint16_t x = rand () % NUM_OF_TILES_PER_SIDE + 1,
            y = rand () % NUM_OF_TILES_PER_SIDE + 1;
        uint16_t w = (rand () % MIN_ROOM_WIDTH_HEIGHT) + MIN_ROOM_WIDTH_HEIGHT,
            h = (rand () % MIN_ROOM_WIDTH_HEIGHT) + MIN_ROOM_WIDTH_HEIGHT;

        if (x + MIN_ROOM_WIDTH_HEIGHT > NUM_OF_TILES_PER_SIDE - 2)
        {
            x = NUM_OF_TILES_PER_SIDE - MIN_ROOM_WIDTH_HEIGHT - 2;
            w = MIN_ROOM_WIDTH_HEIGHT;
        }

        if (y + MIN_ROOM_WIDTH_HEIGHT > NUM_OF_TILES_PER_SIDE - 2)
        {
            y = NUM_OF_TILES_PER_SIDE - MIN_ROOM_WIDTH_HEIGHT - 2;
            h = MIN_ROOM_WIDTH_HEIGHT;
        }

        bool valid = true;
        for (unsigned int j = 0; j < Vector_size (rooms) && valid; j++)
        {
            Room *room = Vector_at (rooms, j);

            if (room->intersects (room, x, y, w, h))
                valid = false;
        }

        if (valid)
        {
            Room room;
            Room_init (&room, x, y, w, h);

            Vector_push (rooms, room);

            uint16_t xc = 0, yc = 0;
            for (uint16_t j = 0; j < w * h; j++)
            {
                Tile tile;
                Tile_init (&tile, x * getTileWidth () + xc * getTileWidth (),
                    y * getTileWidth () + yc * getTileWidth (), getTileWidth (),
                    BLOCK_BORDER, BLOCK_FILL);

                Vector_push (tiles, tile);

                xc++;
                if (xc >= w)
                {
                    xc = 0;
                    yc++;
                }
            }
        }
    }

    Vector_destroy (rooms);*/
}

void input ()
{
    ALLEGRO_EVENT   event;
    ALLEGRO_TIMEOUT timeout;

    al_init_timeout (&timeout, 0.05);

    bool getEvent = al_wait_for_event_until (eventQueue, &event, &timeout);

    if (getEvent && event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
        running = false;
}

void render ()
{
    int w = al_get_display_width (display);

    al_clear_to_color (al_map_rgb (0, 0, 0));
    al_draw_filled_rectangle (0, 0, w, w, BLOCK_BORDER);
    al_draw_filled_rectangle (getTileWidth (), getTileWidth (),
        w - getTileWidth (), w - getTileWidth (), al_map_rgb (0, 0, 0));

    for (size_t i = 0; i < Vector_size (tiles); i++)
    {
        Tile *tile = Vector_at (tiles, i);

        unsigned int x  = tile->getX (tile), y = tile->getY (tile),
            s = tile->getSize (tile);
        ALLEGRO_COLOR b = tile->getBorderColor (tile),
            f = tile->getFillColor (tile);

        al_draw_filled_rectangle (x, y, x + s, y + s, f);
        al_draw_rectangle (x, y, x + s, y + s, b, 1);
    }

    al_flip_display ();
}

void update ()
{

}

static uint8_t getTileWidth ()
{
    return al_get_display_width (display) / NUM_OF_TILES_PER_SIDE;
}
