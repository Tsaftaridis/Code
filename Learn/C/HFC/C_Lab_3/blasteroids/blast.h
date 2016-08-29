#include "spaceship.h"
#define PI 3.14
#define RADIANS(x) x*PI/128

typedef struct blast
{
	float sx;
	float sy;
	float heading;
	float speed;
	int gone;
	ALLEGRO_COLOR color;
	struct blast *next;
} blast;

void draw_blasts();
void move_blast();
void create_blast(spaceship *s);
void manage_blasts();
