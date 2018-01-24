#include "Application.h"

#include <stdio.h>

typedef char* string;

int main (int argc, char **argv)
{
    Vector *test = Vector_new ();
    Vector_append (test, Block_create (0, 0, al_map_rgb (0, 0, 0)));
    Vector_append (test, Block_create (0, 0, al_map_rgb (0, 0, 0)));
    Vector_append (test, Block_create (0, 0, al_map_rgb (0, 0, 0)));
    Vector_free_d (test, &Block_free);
    
    if (!init ())
        return -1;
    
    al_clear_to_color (al_map_rgb (0, 0, 0));
    al_flip_display ();

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
    al_flip_display ();
}

void update () 
{

}