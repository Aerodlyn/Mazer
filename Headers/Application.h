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

static bool running = true;

static const unsigned int BLOCK_SIZE = 5;

static const uint8_t ROOM_ATTEMPTS = 50;
static const uint16_t MIN_ROOM_WIDTH_HEIGHT = 5, NUM_OF_TILES_PER_SIDE = 50;

static ALLEGRO_DISPLAY      *display    = NULL;
static ALLEGRO_EVENT_QUEUE  *eventQueue = NULL;

static const ALLEGRO_COLOR BLOCK_BORDER = { 255, 255, 255, 255 };
static const ALLEGRO_COLOR BLOCK_FILL   = { 255, 0, 0, 255 };

static Vector (Tile) *tiles = NULL;

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
