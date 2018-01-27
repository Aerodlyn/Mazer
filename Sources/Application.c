#include "Application.h"

int main (int argc, char **argv)
{
    if (!init ())
    {
        throwError ("Required Allegro components failed to initialize.", -1);
        return -1;
    }

    vector = Vector_create (Tile);
    for (size_t i = 0; i < 50; i++)
        Vector_push (vector, Tile_create (i * 5, i * 5, 5, al_map_rgb (i * 5, i * 5, i * 5)));
    
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

    display = al_create_display (640, 480);

    if (!display)
        return false;

    eventQueue = al_create_event_queue ();

    if (!eventQueue)
    {
        destroy ();
        return false;
    }

    al_register_event_source (eventQueue, al_get_display_event_source (display));

    return true;
}

void destroy ()
{
    if (display)
        al_destroy_display (display);

    if (eventQueue)
        al_destroy_event_queue (eventQueue);

    if (vector)
        Vector_destroy (vector);
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

    for (size_t i = 0; i < Vector_size (vector); i++)
    {
        Tile *tile = Vector_at (vector, i);

        unsigned int x = tile->getX (tile), y = tile->getY (tile), s = tile->getSize (tile);
        ALLEGRO_COLOR c = tile->getColor (tile);

        al_draw_filled_rectangle (x, y, x + s, y + s, c);
    }

    al_flip_display ();
}

void update () 
{

}