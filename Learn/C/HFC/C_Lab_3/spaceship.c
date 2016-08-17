#include "spaceship.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/transformations.h>

#include <math.h>

#define PI 3.1415
#define REGULAR_DEGREES(x) 360*(x)/256//x = input in allegro_degrees
#define RADIANS(x) (x)*PI/128// x = input in allegro_degrees
#define MAX_SPEED 10
float n = 0.4;

void draw_spaceship(spaceship* s)
{
	ALLEGRO_TRANSFORM transform;
	al_identity_transform(&transform);
	al_rotate_transform(&transform, RADIANS(s->current.allegro_degrees));
	al_translate_transform(&transform, s->sx, s->sy);
	al_use_transform(&transform);
	al_draw_line(-80*n, 90*n, 0*n, -110*n, s->color, n*8.0f);
	al_draw_line(0*n, -110*n, 80*n, 90*n, s->color, n*8.0f);
	al_draw_line(-60*n, 40*n, -10*n, 40*n, s->color, n*8.0f);
	al_draw_line(60*n, 40*n, 10*n, 40*n, s->color, n*8.0f);	 
}

void accelerate_spaceship(spaceship *s)
{
	if(s->current.speed < MAX_SPEED)
	{
		s->current.speed += 0.1;
	}
	s->old.speed = s->current.speed;
	s->old.allegro_degrees = s->current.allegro_degrees;
}

void decelerate_spaceship(spaceship* s)
{
	if(s->old.speed > 0.3)
	{
		s->old.speed -= 0.3;
	}
	else
	{
		s->old.speed = 0;
	}
}

void move_spaceship(spaceship *s)
{
	while(s->current.allegro_degrees >= 256)
	{
		s->current.allegro_degrees -= 256;
	}
	
	//Uncomment the next for a more primitive spaceship! (make sure you comment the one after that).
	//float rad = RADIANS(s->old.allegro_degrees);
	float rad = RADIANS(s->current.allegro_degrees);
	s->sy = s->sy - s->old.speed * cos(rad);
	s->sx = s->sx + s->old.speed * sin(rad);

	if(s->sx < 0)
	{
		s->sx = 1920;
	}
	else if(s->sx > 1920)
	{
		s->sx = 0;
	}
	
	if(s->sy < 0)
	{
		s->sy = 1080;
	}
	else if(s->sy > 1080)
	{
		s->sy = 0;
	}
}