/**
 * @author  Patrick Jahnig (Aerodlyn)
 * @version 2018.06.02
 */

#ifndef MAZER_APPLICATION_H
#define MAZER_APPLICATION_H

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>

// https://wiki.libsdl.org/FrontPage
#include <SDL2/SDL.h>

#include "Tile.h"
#include "Utils.h"

extern const int8_t     WINDOW_PADDING;
extern const int16_t    NUM_OF_TILES_PER_SIDE, WINDOW_HEIGHT, WINDOW_WIDTH;
extern const int32_t    NUM_OF_TILES;

extern void f_determineBorders (Tile* const tiles, const int32_t* const length);

/**
 * Fortran Procedure
 * 
 * Generates the paths between dungeon rooms.
 * 
 * @param   tiles       - The array of tiles contained within the game
 * @param   length      - The length of the tiles array
 * @param   attempts    - The number of paths to attempt to make
 */
extern void f_generatePaths (Tile* const tiles, const int32_t* const length, const int16_t* const attempts);

/**
 * Fortran Procedure
 * 
 * Validates the tiles that occupy the given rectangular space.
 * 
 * @param   tiles   - The array of tiles contained within the game
 * @param   length  - The length of the tiles array
 * @param   x       - The first upper-left coordinate of the region of tiles
 * @param   y       - The second upper-left coordinate of the region of tiles
 * @param   w       - The number of tiles for the region to comprise of horizontally
 * @param   h       - The number of tiles for the region to comprise of vertically
 */
extern void f_generateTiles (Tile* const tiles, const int16_t* const length, const int16_t* const x, const int16_t* const y, 
    const int16_t* const w, const int16_t* const h);

/**
 * 
 */
extern void f_generateRooms (Tile* const tiles, const int32_t* const length, const int16_t* const attempts, const int16_t* 
    const minSize);
    
extern void f_init ();

typedef enum _STATUS
{
    TILE_CREATION_FAILED,
    THREAD_CREATION_FAILED,
    VIDEO_CREATION_FAILED,
    WINDOW_CREATION_FAILED,
    RUNNING,
    SUSPEND_GAMELOOP,
    EXIT
} STATUS;

static bool isKeyDown = false;

static const int16_t    TARGET_FRAME_RATE       = 16700;
static const int16_t    MIN_ROOM_WIDTH_HEIGHT   = 5, PATH_ATTEMPTS = 250, ROOM_ATTEMPTS = 1000;

static const uint8_t BLOCK_BORDER []    = { 255, 255, 255, 255 };
static const uint8_t BLOCK_FILL []      = { 255, 0, 0, 255 };

static SDL_Renderer *renderer   = NULL;
static SDL_Window   *window     = NULL;

static STATUS applicationStatus;

static Tile *tiles = NULL;

int main (int argc, char **argv);

static void clearTiles ();

/**
 * Destoys all dynamically allocated values. 
 */
static void destroy ();

static void input ();

static void render ();

static void update ();

static uint8_t getTileHeight ();

static uint8_t getTileWidth ();

/**
 * Calls generation functions (typed in Fortran).
 */
static STATUS generate ();

/**
 * Attempts to inititalize required SDL objects.
 *
 * @return Returns the enum representing the status of the creation process
 */
static STATUS init ();

#endif
