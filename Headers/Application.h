#ifndef MAZER_APPLICATION_H
#define MAZER_APPLICATION_H

#include <SDL2/SDL.h>

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <time.h>

#define nullptr NULL

#include "Room.h"
#include "Tile.h"
#include "Utils.h"
// #include "_Vector.h"

extern void f_generatePaths (Tile*, const int16_t*, const int16_t*, const int8_t*);
extern void f_generateRooms (Room*, const int16_t*, const int16_t*, const int16_t*, const int8_t*);

typedef enum _STATUS
{
    SURFACE_CREATION_FAILED,
    VIDEO_CREATION_FAILED,
    WINDOW_CREATION_FAILED,
    RUNNING,
    EXIT
} STATUS;

static const int8_t     WINDOW_PADDING          = 1;
static const int16_t    MIN_ROOM_WIDTH_HEIGHT   = 5, ROOM_ATTEMPTS = 1000, NUM_OF_TILES_PER_SIDE = 75;

static const uint8_t BLOCK_BORDER []    = { 255, 255, 255, 255 };
static const uint8_t BLOCK_FILL []      = { 255, 0, 0, 255 };

static int32_t windowWidth, windowHeight;

static SDL_Renderer *renderer   = nullptr;
static SDL_Window   *window     = nullptr;

static STATUS applicationStatus;

static Tile *tiles = nullptr;

int main (int argc, char **argv);

static void destroy ();

static void generate ();

static void generateRooms ();

static void input ();

static void render ();

static void update ();

static uint8_t getTileHeight ();

static uint8_t getTileWidth ();

/**
 * Attempts to inititalize required SDL objects.
 *
 * @return Returns the enum representing the status of the creation process
 */
static STATUS init ();

#endif
