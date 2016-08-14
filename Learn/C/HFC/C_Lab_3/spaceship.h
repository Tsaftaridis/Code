#include <allegro5/allegro.h>
#include <allegro5/allegro_color.h>
#include <stdio.h>

typedef struct
{
	float sx;
	float sy;
	float heading;
	float speed; 
	int gone;
	ALLEGRO_COLOR color;	
} spaceship;

void draw_spaceship(spaceship* s);