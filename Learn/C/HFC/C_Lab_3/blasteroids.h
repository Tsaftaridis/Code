#define al_init()    (al_install_system(ALLEGRO_VERSION_INT, atexit))

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "spaceship.h"
#include "asteroid.h"
#include "blast.h"

void error(char* msg);
void* keys(ALLEGRO_THREAD* a, void* b);
