#include "spaceship.h"

#define MAX_SPEED (float)10//120 pixels per second, 2 pixels per frame, 0.2 pixels per timer tick...
#define AL_DEG_STEP (float)256/150//256 al_deg per second, 256/20 al_deg per frame, 256/200 al_deg per timer tick...

float SCREEN_W;

data_t0 graphics_variables;

void draw_spaceship(spaceship* s)
{
	ALLEGRO_TRANSFORM tr;
	al_identity_transform(&tr);
	al_rotate_transform(&tr, RADIANS(s->current.allegro_degrees));
	al_translate_transform(&tr, s->sx, s->sy);
	al_use_transform(&tr);
	// Change the graphics depending on the screen size(the originals were created for 1080p display)
	float change = SCREEN_W/1080;
	float n = 0.2*change; // Drawing scale.
	al_draw_line(-80*n, 90*n, 0*n, -110*n, s->color, n*8.0f);
	al_draw_line(0*n, -110*n, 80*n, 90*n, s->color, n*8.0f);
	al_draw_line(-60*n, 40*n, -10*n, 40*n, s->color, n*8.0f);
	al_draw_line(60*n, 40*n, 10*n, 40*n, s->color, n*8.0f);
}


void accelerate_spaceship(spaceship *s)
{
	if(s->current.speed < MAX_SPEED)
	{
		s->current.speed += MAX_SPEED/100.0;
	}
	s->old.speed = s->current.speed;
	s->old.allegro_degrees = s->current.allegro_degrees;
}

void decelerate_spaceship(spaceship* s)
{
	if(s->old.speed > MAX_SPEED/100.0)
	{
		s->old.speed -= MAX_SPEED/100.0;
	}
	else
	{
		s->old.speed = 0;
		s->current.speed = 0;
	}
}

void increase_angle(spaceship *s)
{
	s->current.allegro_degrees += AL_DEG_STEP;
}

void decrease_angle(spaceship *s)
{
	s->current.allegro_degrees -= AL_DEG_STEP;
}

void move_spaceship(spaceship *s)
{
	while(s->current.allegro_degrees >= 256)
	{
		s->current.allegro_degrees -= 256;
	}

	//Uncomment the next for a more advanced spaceship! (make sure you comment the one after that).
	float rad = RADIANS(s->old.allegro_degrees);
	//float rad = RADIANS(s->current.allegro_degrees);
	s->sy = s->sy - s->old.speed *(long double) cos(rad);
	s->sx = s->sx + s->old.speed *(long double) sin(rad);

	if(s->sx < 0)
	{
		s->sx = graphics_variables.SCREEN_WIDTH;
	}
	else if(s->sx > graphics_variables.SCREEN_WIDTH)
	{
		s->sx = 0;
	}


	if(s->sy < 0)
	{
		s->sy = graphics_variables.SCREEN_LENGTH;
	}
	else if(s->sy > graphics_variables.SCREEN_LENGTH)
	{
		s->sy = 0;
	}
}
