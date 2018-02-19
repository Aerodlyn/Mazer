#ifndef MAZER_APPLICATION_H
#define MAZER_APPLICATION_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <time.h>

#include "Room.h"
#include "Tile.h"
#include "Utils.h"
#include "_Vector.h"

extern void f_generatePaths (Tile*, const int16_t*, const int16_t*, const int8_t*);
extern void f_generateRooms (Room*, const int16_t*, const int16_t*, const int16_t*, const int8_t*);

static bool running = true;

static const int8_t WINDOW_PADDING = 1;
static const int16_t MIN_ROOM_WIDTH_HEIGHT = 5, ROOM_ATTEMPTS = 1000, NUM_OF_TILES_PER_SIDE = 75;

static ALLEGRO_DISPLAY      *display    = NULL;
static ALLEGRO_EVENT_QUEUE  *eventQueue = NULL;

static const ALLEGRO_COLOR BLOCK_BORDER = { 255, 255, 255, 255 };
static const ALLEGRO_COLOR BLOCK_FILL   = { 255, 0, 0, 255 };

static Tile *tiles = NULL;
//static Vector (Tile) *tiles = NULL;

int main (int argc, char **argv);

/**
 * Attempts to inititalize required Allegro objects.
 *
 * @return Returns false if any Allegro object was unable to be created, true
 *          otherwise
 */
static bool init ();

static void destroy ();

static void generate ();

static void generateRooms ();

static void input ();

static void render ();

static void update ();

static uint8_t getTileWidth ();

#endif
