#include "asteroid.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>

typedef struct
{
	float sx;
	float sy;
	float heading;
	float twist;
	float speed;
	float ang_velocity;
	float scale;
	int gone;
	ALLEGRO_COLOR color;
}asteroid;

void draw_asteroid_origin(asteroid* a)
{
	al_draw_line(-20, 20, -25, 5, a->color, 2.0f);
	al_draw_line(-25, 5, -25, -10, a->color, 2.0f);
	al_draw_line(-25,-10, -5, -10, a->color, 2.0f);
	al_draw_line(-5, -10, -10, -20, a->color, 2.0f);
	al_draw_line(-10, -20, 5, -20, a->color, 2.0f);
	al_draw_line(5, -20, 20, -10, a->color, 2.0f);
	al_draw_line(20, -10, 20, -5, a->color, 2.0f);
	al_draw_line(20, -5, 0, 0, a->color, 2.0f);
	al_draw_line(0, 0, 20, 10, a->color, 2.0f);
	al_draw_line(20, 10, 10, 20, a->color, 2.0f);
	al_draw_line(10, 20, 0, 15, a->color, 2.0f);
	al_draw_line(-20, 20, -25, 5, a->color, 2.0f);
	al_draw_line(10, 20, 0, 15, a->color, 2.0f);
	al_draw_line(0, 15, -20, 20, a->color, 2.0f);
}

void move_asteroids()
{
	//TODO updates the variables for the position of each asteroid depending on the 
	// velocity of each one...
}

void draw_asteroids()
{
	//TODO: draws all asteroids according to the updated positions.
}

void split_asteroid()
{
	//TODO: splits and asteroid in two, according to the spec.	
}

void destroy_asteroid()
{
	//?? TODO
}