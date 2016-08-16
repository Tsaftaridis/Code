#include "spaceship.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/transformations.h>

#include <math.h>

#define MAX_SPEED 10
float n = 0.4;

float degrees_to_al(float x)
{
	return x*12.4/720;
}

float al_to_degrees(float x)
{
	return x*720/12.4000003;
}


void draw_spaceship(spaceship* s)
{
	ALLEGRO_TRANSFORM transform;
	al_identity_transform(&transform);
	al_rotate_transform(&transform, degrees_to_al(s->current.angle));
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
	s->old.angle = s->current.angle;
}

void decelerate_spaceship(spaceship *s)
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

void move_spaceship(spaceship* s)
{
	
	
	
	int direction = ((int)(s->old.angle)%359);
	if( direction == 90 || direction == 270)
	{
		s->sy = s->sy + s->old.speed;
	}
	else if(direction == 0 || direction == 180)
	{
		s->sx = s->sx + s->old.speed;
	}
	else if(direction > 0 && direction < 90)//sin > 0, cos > 0....
	{
		printf("One");
		s->sy = s->sy - s->old.speed*cos(direction);
		s->sx = s->sx + s->old.speed*sin(direction);
	}
	else if(direction > 90 && direction < 180)// sin > 0, cos < 0....
	{
		printf("Two");
		s->sy -= s->old.speed*cos(direction);
		s->sx += s->old.speed*sin(direction);
	}
	else if(direction > 180 && direction < 270)// sin < 0, cos < 0....
	{
		printf("Three");
		s->sy -= s->old.speed*cos(direction);
		s->sx += s->old.speed*sin(direction);
	}
	else if(direction > 270 && direction < 360)// sin < 0, cos > 0....
	{
		printf("Four");
		s->sy -= s->old.speed*cos(direction);
		s->sx += s->old.speed*sin(direction);
	}

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