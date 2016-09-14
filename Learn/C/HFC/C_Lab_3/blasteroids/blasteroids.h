#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#include "asteroid.h"
#include "blast.h"
#include "structs.h"

#define FPS 60

#ifndef NUM_OF_ASTEROIDS
#define NUM_OF_ASTEROIDS 4
#endif

typedef struct ALLEGRO_DISPLAY ALLEGRO_DISPLAY;
typedef struct ALLEGRO_COND ALLEGRO_COND;


typedef struct data_t1
{
	control* myself;
	spaceship *s_p;
	bool do_accelerate;
	bool do_decelerate;
	bool do_turn_left;
	bool do_turn_right;
}data_t1;

void error(char *msg);
void *objects(ALLEGRO_THREAD *thread, void *objects_variables);
void *graphics(ALLEGRO_THREAD *thread, void *vars);
void draw_text(char *s);
