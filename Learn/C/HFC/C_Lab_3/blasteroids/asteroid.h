#include <math.h>
#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include "structs.h"

typedef struct asteroid
{
	float sx;
	float sy;
	float heading;
	float twist;
	float speed;
	float ang_velocity;
	float scale;
	int gone;
	int to_go;
	ALLEGRO_COLOR color;
	struct asteroid *next;
}asteroid;

void draw_asteroids();
void create_asteroid();
void initialize_asteroids();
void move_asteroids();
void manage_asteroids();
int randint(int n);
// Hanlde asteroids that are hit by a blast
void asteroid_break(int n);
