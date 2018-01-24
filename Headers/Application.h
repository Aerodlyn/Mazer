#ifndef MAZER_APPLICATION_H
#define MAZER_APPLICATION_H

#include <allegro5/allegro.h>

#include <stdbool.h>

#include "Block.h"
#include "Vector.h"

static bool running = true;

static ALLEGRO_DISPLAY      *display    = NULL;
static ALLEGRO_EVENT_QUEUE  *eventQueue = NULL;

int main (int argc, char **argv);

/**
 * Attempts to inititalize required Allegro objects.
 *
 * @return Returns false if any Allegro object was unable to be created, true otherwise
 */
static bool init ();

static void destroy ();

static void input ();

static void render ();

static void update ();

#endif 
