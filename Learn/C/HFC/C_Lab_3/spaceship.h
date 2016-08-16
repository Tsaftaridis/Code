#include <allegro5/allegro.h>
#include <allegro5/allegro_color.h>
#include <stdio.h>

typedef struct
{
	float speed;
	float angle;
}vector;

typedef struct
{
	float sx;
	float sy;
	vector current;
	vector old;
	int gone;
	ALLEGRO_COLOR color;	
} spaceship;

void draw_spaceship(spaceship* s);
void accelerate_spaceship(spaceship* s);
void decelerate_spaceship(spaceship* s);
void move_spaceship(spaceship* s);