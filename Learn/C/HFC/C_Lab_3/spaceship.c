#include "spaceship.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/transformations.h>

#include <math.h>

#define DEGREES(x) (float)((x)/360.0*0xFFFFFF)

void draw_spaceship(spaceship* s)
{
	ALLEGRO_TRANSFORM transform;
	al_identity_transform(&transform);
	al_rotate_transform(&transform, DEGREES(s->heading));
	al_translate_transform(&transform, s->sx, s->sy);
	al_use_transform(&transform);
	al_draw_line(-80, 90, 0, -110, s->color, 8.0f);
	al_draw_line(0, -110, 80, 90, s->color, 8.0f);
	al_draw_line(-60, 40, -10, 40, s->color, 8.0f);
	al_draw_line(60, 40, 10, 40, s->color, 8.0f);	 
}