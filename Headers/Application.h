#ifndef MAZER_APPLICATION_H
#define MAZER_APPLICATION_H

#include <pthread.h>
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

extern void f_generatePaths (Tile*, const int32_t*, const int16_t*);
extern void f_generateTiles (Tile*, const int16_t*, const int16_t*, const int16_t*, const int16_t*, const int16_t*);
extern void f_generateRooms (Tile*, const int32_t*, const int16_t*, const int16_t*);
extern void f_init ();

typedef enum _STATUS
{
    TILE_CREATION_FAILED,
    THREAD_CREATION_FAILED,
    VIDEO_CREATION_FAILED,
    WINDOW_CREATION_FAILED,
    RUNNING,
    STARTING,
    EXIT
} STATUS;

static const int16_t    TARGET_FRAME_RATE       = 16700;
static const int16_t    MIN_ROOM_WIDTH_HEIGHT   = 5, PATH_ATTEMPTS = 250, ROOM_ATTEMPTS = 1000;

static const uint8_t BLOCK_BORDER []    = { 255, 255, 255, 255 };
static const uint8_t BLOCK_FILL []      = { 255, 0, 0, 255 };

static pthread_t        gameloopThread;
static pthread_attr_t   gameloopAttr;
static pthread_cond_t   gameloopCond;
static pthread_mutex_t  applicationStatusMutex;

static SDL_Renderer *renderer   = NULL;
static SDL_Window   *window     = NULL;

static STATUS applicationStatus = STARTING;

static Tile *tiles = NULL;

int main (int argc, char **argv);

static void destroy ();

static void generate ();

static void input ();

static void render ();

static void update ();

static void* gameloop ();

static uint8_t getTileHeight ();

static uint8_t getTileWidth ();

/**
 * Attempts to inititalize required SDL objects.
 *
 * @return Returns the enum representing the status of the creation process
 */
static STATUS init ();

#endif
