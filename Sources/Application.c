#include "Application.h"

int main (int argc, char **argv)
{
    applicationStatus = init ();
    while (applicationStatus == RUNNING) 
    {
        input ();
        render ();
    }

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

    tiles = calloc (NUM_OF_TILES_PER_SIDE * NUM_OF_TILES_PER_SIDE, sizeof (Tile));
    int16_t tileAttempts = ROOM_ATTEMPTS;

    generateRooms ();
    f_generatePaths (tiles, &NUM_OF_TILES_PER_SIDE, &tileAttempts, &WINDOW_PADDING);

    /*for (int16_t i = 0; i < NUM_OF_TILES_PER_SIDE * NUM_OF_TILES_PER_SIDE; i++)
    {
        Tile t = tiles [i];

        if (!t.valid)
            continue;

        if (t.fillColor [0] != 255)
            printf ("%d, %d, %d, %d\n", t.fillColor [0], t.fillColor [1], t.fillColor [2], t.fillColor [3]);
    }*/
}

void generateRooms ()
{
    Room *rooms = calloc (ROOM_ATTEMPTS, sizeof (Room));
    f_generateRooms (rooms, &ROOM_ATTEMPTS, &MIN_ROOM_WIDTH_HEIGHT, &NUM_OF_TILES_PER_SIDE, 
        &WINDOW_PADDING);
    
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
            Tile_init (&tile, x + xc, y + yc, 1, 1, BLOCK_FILL, BLOCK_BORDER);

            tiles [(x + xc - 1) + NUM_OF_TILES_PER_SIDE * (y + yc - 1)] = tile;

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
    SDL_Rect windowBorder = { tw, th, windowWidth - tw * 2, windowHeight - th * 2 };

    SDL_SetRenderDrawColor (renderer, 255, 255, 255, 255);
    SDL_RenderClear (renderer);

    SDL_SetRenderDrawColor (renderer, 0, 0, 0, 255);
    SDL_RenderFillRect (renderer, &windowBorder);

    for (int16_t i = 0; i < NUM_OF_TILES_PER_SIDE * NUM_OF_TILES_PER_SIDE; i++)
    {
        Tile t = tiles [i];
        if (!t.valid)
            continue;

        uint8_t tw = getTileWidth (), th = getTileHeight ();
        // uint8_t *tb = t.getBorderColor (&t), *tf = t.getFillColor (&t);
        int16_t x = t.x * tw, y = t.y * th, w = t.w * tw, h = t.h * h;
        
        //t.getSize (&t, &w, &h);
        //w *= tw;
        //h *= th;

        SDL_Rect r = { x, y, tw, th };
        SDL_SetRenderDrawColor (renderer, BLOCK_FILL [0], BLOCK_FILL [1], BLOCK_FILL [2], BLOCK_FILL [3]);
        SDL_RenderFillRect (renderer, &r);
        SDL_SetRenderDrawColor (renderer, BLOCK_BORDER [0], BLOCK_BORDER [1], BLOCK_BORDER [2], BLOCK_BORDER [3]);
        SDL_RenderDrawRect (renderer, &r);
    }

    SDL_RenderPresent (renderer);
}

void update ()
{

}

static uint8_t getTileHeight () { return (uint8_t) (windowHeight / NUM_OF_TILES_PER_SIDE); }

static uint8_t getTileWidth () { return (uint8_t) (windowWidth / NUM_OF_TILES_PER_SIDE); }

/**
 * Attempts to inititalize required SDL objects.
 *
 * @return Returns the enum representing the status of the creation process
 */
static STATUS init ()
{
    if (SDL_Init (SDL_INIT_VIDEO))
        return VIDEO_CREATION_FAILED;

    if (SDL_CreateWindowAndRenderer (525, 525, SDL_WINDOW_RESIZABLE, &window, &renderer))
        return WINDOW_CREATION_FAILED;

    SDL_GetWindowSize (window, &windowWidth, &windowHeight);
    generate ();

    return RUNNING;
}
