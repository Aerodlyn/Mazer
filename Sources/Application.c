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

    display = al_create_display (650, 650);

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
    Room *rooms = calloc (ROOM_ATTEMPTS, sizeof (Room));
    f_generateRooms (rooms, &ROOM_ATTEMPTS, &MIN_ROOM_WIDTH_HEIGHT, &NUM_OF_TILES_PER_SIDE, &WINDOW_PADDING);
    
    for (int i = 0; i < ROOM_ATTEMPTS; i++)
    {
        int x = rooms [i].x, y = rooms [i].y;
        int w = rooms [i].w, h = rooms [i].h;

        // Don't add room if it overlaps another
        if (!rooms [i].valid)
            continue;

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

    free (rooms);
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
