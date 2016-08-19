#include <math.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>

#define PI 3.14
#define RADIANS(x) x*PI/128
#define MAX_SPEED 100 // 5 pixels/cycle 

typedef struct

{
	float speed;
	float allegro_degrees;
}vector;

typedef struct
{
	float sx;
	float sy;
	vector current;
	vector old;
	bool gone;
	ALLEGRO_COLOR color;	
} spaceship;

void draw_spaceship(spaceship *s);
void accelerate_spaceship(spaceship *s);
void decelerate_spaceship(spaceship* s);
void move_spaceship(spaceship *s);
void increase_angle(spaceship *s);
void decrease_angle(spaceship *s);