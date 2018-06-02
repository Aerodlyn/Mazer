#include "Application.h"

/**
 * Handles the core functionality of Mazer; rendering and updating based on user input. All generation code is handled by 
 *  Fortran procedures which are called by the generate method defined in this file.
 * 
 * @author  Patrick Jahnig (Aerodlyn)
 * @version 2018.06.02
 */

int main (int argc, char **argv)
{
    applicationStatus = init ();    
    while (applicationStatus == RUNNING)
    {
        input ();
        update ();
        render ();
    }

    destroy ();
    return applicationStatus;
}

/**
 * Destoys all dynamically allocated values. 
 */
void destroy ()
{
    if (renderer)
        SDL_DestroyRenderer (renderer);

    if (window)
        SDL_DestroyWindow (window);

    if (tiles)
        free (tiles);

    SDL_Quit ();
}

/**
 * Handles input from the user (keyboard only).
 */
void input ()
{
    SDL_Event evt;
    while (SDL_PollEvent (&evt))
    {
        switch (evt.type)
        {
            case SDL_KEYDOWN:
                if (isKeyDown)
                    break;

                switch (evt.key.keysym.sym)
                {
                    case SDLK_g:                        
                        // applicationStatus = generate ();
                        break; 

                    case SDLK_q:
                        applicationStatus = EXIT;
                        break;
                }

                isKeyDown = true;
                break;

            case SDL_KEYUP:
                isKeyDown = false;
                break;

            case SDL_QUIT:
                applicationStatus = EXIT;
                break;
        }
    }
}

/**
 * Renders all valid tiles to the screen. Invalid tiles are rendered as black space (the background).
 */
void render ()
{
    uint8_t tw = getTileWidth (), th = getTileHeight ();

    SDL_SetRenderDrawColor (renderer, 0, 0, 0, 255);
    SDL_RenderClear (renderer);
    
    for (int32_t i = 0; i < NUM_OF_TILES; i++)
    {
        Tile t = tiles [i];
        if (!t.valid)
            continue;

        int16_t tx = (i % NUM_OF_TILES_PER_SIDE) * tw, 
            ty = (i / NUM_OF_TILES_PER_SIDE) * th;
        uint8_t borders = Tile_getTileBorders (&t);
        SDL_Color tb = t.getBorderColor (&t), tf = t.getFillColor (&t);

        SDL_Rect r = { tx, ty, tw - (i % NUM_OF_TILES_PER_SIDE == NUM_OF_TILES_PER_SIDE - 1 ? 1 : 0), 
                        th - (i / NUM_OF_TILES_PER_SIDE == NUM_OF_TILES_PER_SIDE - 1 ? 1 : 0) };
        SDL_SetRenderDrawColor (renderer, tf.r, tf.g, tf.b, tf.a);
        SDL_RenderFillRect (renderer, &r);
        
        SDL_SetRenderDrawColor (renderer, tb.r, tb.g, tb.b, tb.a);
        if (borders & BOTTOM)
            SDL_RenderDrawLine (renderer, r.x, r.y + r.h, r.x + r.w, r.y + r.h);

        if (borders & LEFT)
            SDL_RenderDrawLine (renderer, r.x, r.y, r.x, r.y + r.h);

        if (borders & RIGHT)
            SDL_RenderDrawLine (renderer, r.x + r.w, r.y, r.x + r.w, r.y + r.h);

        if (borders & TOP)
            SDL_RenderDrawLine (renderer, r.x, r.y, r.x + r.w, r.y);
    }

    SDL_RenderPresent (renderer);
}

/**
 * Updates game conditions based on user input.
 * NOTE: Unused at the moment.
 */
void update () {}

/**
 * Returns the height of each tile.
 * 
 * @return The height of each tile
 */
static uint8_t getTileHeight () { return (uint8_t) (WINDOW_HEIGHT / NUM_OF_TILES_PER_SIDE); }

/**
 * Returns the width of each tile.
 * 
 * @return The width of each tile
 */
static uint8_t getTileWidth () { return (uint8_t) (WINDOW_WIDTH / NUM_OF_TILES_PER_SIDE); }

/**
 * Calls generation functions (typed in Fortran).
 */
static Status generate ()
{
    clearTiles ();

    srand (time (NULL));
    f_generateRooms (tiles, &NUM_OF_TILES, &ROOM_ATTEMPTS, &MIN_ROOM_WIDTH_HEIGHT);
    f_generatePaths (tiles, &NUM_OF_TILES, &PATH_ATTEMPTS);
    f_determineBorders (tiles, &NUM_OF_TILES);

    return RUNNING;
}

/**
 * Attempts to inititalize required SDL objects.
 *
 * @return Returns the enum representing the status of the creation process
 */
static Status init ()
{  
    f_init ();

    if (SDL_Init (SDL_INIT_VIDEO))
        return VIDEO_CREATION_FAILED;

    if (SDL_CreateWindowAndRenderer (WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_RESIZABLE, &window, &renderer))
        return WINDOW_CREATION_FAILED;

    SDL_SetWindowResizable (window, SDL_FALSE);

    tiles = calloc (NUM_OF_TILES, sizeof (Tile));
    if (!tiles)
        return TILE_CREATION_FAILED;

    return generate ();
}
