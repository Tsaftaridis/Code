#include "spaceship.h"
#include "blast.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>

#include <math.h>

#define PI 3.1415
#define RADIANS(x) (x)*PI/128// x = input in allegro_degrees

#define SCREEN_W 1920
#define SCREEN_L 1080

static unsigned int shot_no = 0;

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

struct blast *root = NULL;
struct blast *conductor = NULL;

void create_blast(spaceship *s)
{
	if(root == NULL)
	{
		root = (struct blast*) malloc(sizeof(blast));
		root->next = NULL;
		root->gone = 0;
	}
	conductor = root;
	
	while(conductor->next != NULL)
	{
		conductor = conductor->next;
	}
	
	conductor->next = malloc(sizeof(blast));
	conductor = conductor->next;
	
	if(conductor == NULL)
	{
		printf("Out of memory\n");
		exit(-1);
	}
	
	conductor->next = NULL;
	conductor->heading = s->current.allegro_degrees;
	conductor->speed = 30;
	conductor->sx = s->sx;
	conductor->sy = s->sy;
	conductor->color = al_map_rgb(255,0,255);
	conductor->gone = 0;
}

void draw_blasts()
{
	if(root != NULL)
	{
		conductor = root;
		while(conductor->next != NULL)
		{
			conductor = conductor->next;
			if(conductor->sx < 0 || conductor->sy < 0 || conductor->sx > 1920 || conductor->sy > 1080)
			{
				conductor->gone = 1;
			}
			
			if(conductor->gone == 0)
			{
				ALLEGRO_TRANSFORM transform;
				al_identity_transform(&transform);
				al_translate_transform(&transform, conductor->sx, conductor->sy);
				al_use_transform(&transform);
				al_draw_line(0, 0, 6, 0, conductor->color, 1.0f);
				al_draw_line(0, 1, 6, 1, conductor->color, 1.0f);
				al_draw_line(0, 2, 6, 2, conductor->color, 1.0f);
				al_draw_line(0, 3, 6, 3, conductor->color, 1.0f);
			}
		}
	}
}

void destroy_blasts()
{
	struct blast *temp = NULL;
	if(root != NULL)
	{
		conductor = root;
		
		// Reach the end of the linked list 
		while(conductor->next != NULL)
		{
			conductor = conductor->next;
			if(conductor->gone == 1)
			{
				temp = conductor;
				conductor = conductor->next;
				free(temp);
			}
		}
		
	}	
}

void move_blast()
{
	if(root != NULL)
	{
		conductor = root;
		while(conductor->next != NULL)
		{
			conductor->sx += conductor->speed * sin(RADIANS(conductor->heading));
			conductor->sy -= conductor->speed * cos(RADIANS(conductor->heading));
		}
	}
}