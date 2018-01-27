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
 * @return Returns false if any Allegro object was unable to be created, true otherwise
 */
bool init ()
{
    if (!al_init ())
        return false;

    display = al_create_display (640, 640);

    if (!display)
        return false;

    eventQueue = al_create_event_queue ();

    if (!eventQueue)
    {
        destroy ();
        return false;
    }

    al_register_event_source (eventQueue, al_get_display_event_source (display));

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
    int w = al_get_display_width (display);
    tiles = Vector_create (Tile);

    unsigned int tn = 250, tw = (w * 1.4142) / tn - 1;

    for (size_t i = 0; i < tn; i++)
    {
        Tile tile;
        Tile_init (&tile, i * tw, 0, (i + 1) * tw, al_map_rgb (i * 255 / tn, 0, 0));

        Vector_push (tiles, tile);
    }

    for (size_t i = 0; i < tn; i++)
    {
        Tile tile;
        Tile_init (&tile, 0, i * tw, (i + 1) * tw, al_map_rgb (0, 0, i * 255 / tn));

        Vector_push (tiles, tile);
    }

    for (size_t i = 0; i < tn; i++)
    {
        Tile tile;
        Tile_init (&tile, i * tw, i * tw, (i + 1) * tw, al_map_rgb (0, i * 255 / tn, 0));

        Vector_push (tiles, tile);
    }

    printf ("Number of tiles generated: %lu\n", Vector_size (tiles));
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
    al_clear_to_color (al_map_rgb (0, 0, 0));

    for (size_t i = 0; i < Vector_size (tiles); i++)
    {
        Tile *tile = Vector_at (tiles, i);

        unsigned int x  = tile->getX (tile), y = tile->getY (tile), s = tile->getSize (tile);
        ALLEGRO_COLOR c = tile->getColor (tile);
        
        al_draw_filled_rectangle (x, y, x + s, y + s, c);
    }

    al_flip_display ();
}

void update () 
{

}
