#include "blast.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>

typedef struct
{
	float sx;
	float sy;
	float heading;
	float speed;
	int gone;
	ALLEGRO_COLOR color;
}blast;

void create_blast()
{
	//TODO
	// Direction of the spaceship and travel in a straight line at
	// constant speed (e.g. 3x the max speed of the spaceship)
}

void destroy_blast()
{
	//TODO
}