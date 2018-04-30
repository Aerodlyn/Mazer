#include "Application.h"

int main (int argc, char **argv)
{
    applicationStatus = init ();
    while (applicationStatus == RUNNING)
        input ();

    destroy ();
    return applicationStatus;
}

void destroy ()
{
    if (renderer)
        SDL_DestroyRenderer (renderer);

    if (window)
        SDL_DestroyWindow (window);

    SDL_Quit ();

    if (tiles)
        free (tiles);
}

void generate ()
{
    srand (time (NULL));
    f_generateRooms (tiles, &NUM_OF_TILES, &ROOM_ATTEMPTS, &MIN_ROOM_WIDTH_HEIGHT);

    // f_generatePaths (tiles, &NUM_OF_TILES_PER_SIDE, &tileAttempts, &WINDOW_PADDING);
}

void input ()
{
    SDL_Event evt;
    while (SDL_PollEvent (&evt))
    {
        switch (evt.type)
        {
            case SDL_QUIT:
                applicationStatus = EXIT;
                break;
        }
    }
}

void render ()
{
    uint8_t tw = getTileWidth (), th = getTileHeight ();

    SDL_SetRenderDrawColor (renderer, 0, 0, 0, 255);
    SDL_RenderClear (renderer);

    for (int16_t i = 0; i < NUM_OF_TILES; i++)
    {
        Tile t = tiles [i];
        if (!t.valid)
            continue;

        int16_t tx = (i % NUM_OF_TILES_PER_SIDE) * tw, 
            ty = ((i / NUM_OF_TILES_PER_SIDE)) * th;
        SDL_Color tb = t.getBorderColor (&t), tf = t.getFillColor (&t);

        SDL_Rect r = { tx, ty, tw, th };
        SDL_SetRenderDrawColor (renderer, tf.r, tf.g, tf.b, tf.a);
        SDL_RenderFillRect (renderer, &r);
        SDL_SetRenderDrawColor (renderer, tb.r, tb.g, tb.b, tb.a);
        SDL_RenderDrawRect (renderer, &r);
    }

    SDL_RenderPresent (renderer);
}

void update ()
{

}

void* gameloop () 
{
    while (applicationStatus == RUNNING)
    {
        update ();
        render ();

        usleep (TARGET_FRAME_RATE);
    }

    pthread_exit (NULL);
}

static uint8_t getTileHeight () { return (uint8_t) (WINDOW_HEIGHT / NUM_OF_TILES_PER_SIDE); }

static uint8_t getTileWidth () { return (uint8_t) (WINDOW_WIDTH / NUM_OF_TILES_PER_SIDE); }

/**
 * Attempts to inititalize required SDL objects.
 *
 * @return Returns the enum representing the status of the creation process
 */
static STATUS init ()
{  
    f_init ();

    if (SDL_Init (SDL_INIT_VIDEO))
        return VIDEO_CREATION_FAILED;

    if (SDL_CreateWindowAndRenderer (WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_RESIZABLE, &window, &renderer))
        return WINDOW_CREATION_FAILED;

    tiles = calloc (NUM_OF_TILES, sizeof (Tile));
    if (!tiles)
        return TILE_CREATION_FAILED;

    generate ();

    pthread_attr_init (&gameloopAttr);
    pthread_attr_setdetachstate (&gameloopAttr, PTHREAD_CREATE_DETACHED);
    
    if (pthread_create (&gameloopThread, &gameloopAttr, gameloop, NULL))
        return THREAD_CREATION_FAILED;

    pthread_attr_destroy (&gameloopAttr);

    return RUNNING;
}
