#include "asteroid.h"

#ifndef PI
#define PI 3.14
#endif

#ifndef RADIANS
#define RADIANS(x) (x)*PI/128
#endif

int NUM_OF_ASTEROIDS = 4;
int asteroid_coordinates[10][2];

asteroid *root = NULL;
asteroid *maestro = NULL;
asteroid *artist = NULL;
asteroid *shaker = NULL;

data_t0 graphics_variables;

void manage_asteroids()
{
	maestro = root;
	asteroid *prev = NULL;
	prev = root;
	int i, j = 0;

	while(maestro)
	{
		printf("\n\n");
		if(maestro->gone == 0)
		{
			prev = maestro;
			asteroid_coordinates[i][j] = maestro->sx;
			asteroid_coordinates[i][j+1] = maestro->sy;
		}
		else if(maestro->gone == 1)
		{
			if(maestro->next)
			{
				if(maestro == root)
				{
					asteroid *del = root;
					root = root->next;
					del = maestro;
					maestro = root;
					free(del);
				}
				else
				{
					asteroid *del = NULL;
					prev->next = maestro->next;
					del = maestro;
					maestro = prev;
					free(del);
				}
			}
			else
			{
				if(maestro == root)
				{
					root = NULL;
					free(maestro);
					maestro = NULL;
				}
			}
		}
		if(maestro && maestro->next)
			maestro = maestro->next;
		else
			break;
	i++;
	}
	move_asteroids();
}

void draw_asteroids()
{
	if((artist = root))
	{
		do
		{
			ALLEGRO_TRANSFORM transformation;
			al_identity_transform(&transformation);
			al_rotate_transform(&transformation, artist->twist);
			al_translate_transform(&transformation, artist->sx, artist->sy);
			al_use_transform(&transformation);
			float s = artist->scale;
			s *= 2.5;
			al_draw_line(-20*s, 20*s, -25*s, 5*s, artist->color, 4.0f);
			al_draw_line(-25*s, 5*s, -25*s, -10*s, artist->color, 4.0f);
			al_draw_line(-20*s, -10*s, -5*s, -10*s, artist->color, 4.0f);
			al_draw_line(-5*s, -10*s, -10*s, -20*s, artist->color, 4.0f);
			al_draw_line(-10*s, -20*s, 5*s, -20*s, artist->color, 4.0f);
			al_draw_line(5*s, -20*s, 20*s, -10*s, artist->color, 4.0f);
			al_draw_line(20*s, -10*s, 20*s, -5*s, artist->color, 4.0f);
			al_draw_line(20*s, -5*s, 0*s, 0*s, artist->color, 4.0f);
			al_draw_line(0*s, 0*s, 20*s, 10*s, artist->color, 4.0f);
			al_draw_line(20*s, 10*s, 10*s, 20*s, artist->color, 4.0f);
			al_draw_line(10*s, 20*s, 0*s, 15*s, artist->color, 4.0f);
			al_draw_line(0*s, 15*s, -20*s, 20*s, artist->color, 4.0f);
		}while((artist = artist->next));
	}
}

void create_asteroid()
{
	if(!root)
	{
			root = malloc(sizeof(struct asteroid));
			root->sx = 0;
			root->sy = randint(graphics_variables.SCREEN_WIDTH);
			root->next = NULL;
			root->heading = randint(255);
			root->speed = randint(10)+1;
			root->ang_velocity = (float)randint(5)/100.0 + 0.01;
			root->scale = 1;
			root->gone = 0;
			root->twist = randint(255);
			root->color = al_map_rgb(255, 128, 0);
	}
	else
	{
		maestro = root;
		while(maestro->next)
		{
			maestro = maestro->next;
		}

		maestro->next = malloc(sizeof(struct asteroid));
		maestro = maestro->next;

		maestro->sx = 0;
		maestro->sy = randint(graphics_variables.SCREEN_WIDTH);
		maestro->next = NULL;
		maestro->heading = randint(255);
		maestro->speed = randint(10) + 1;
		maestro->ang_velocity = (float)randint(5)/100.0 + 0.01;
		maestro->scale = 1;
		maestro->gone = 0;
		maestro->twist = randint(255);
		maestro->color = al_map_rgb(255, 128, 0);
	}
}

void initialize_asteroids()
{
	for(int i = 0; i < NUM_OF_ASTEROIDS; i++)
	{
		create_asteroid();
	}
}

void move_asteroids()
{
	if((shaker = root))
	{
		do
		{
			shaker->sx += shaker->speed*cos(RADIANS(shaker->heading));
			shaker->sy -= shaker->speed*sin(RADIANS(shaker->heading));
			shaker->twist += shaker->ang_velocity;
			// The readings are actually SCREEN_LENGTH: 1080; SCREEN_WIDTH: 1920;
			if(shaker->sx > graphics_variables.SCREEN_WIDTH)
				{
					shaker->sy = 0;
				}
				else if(shaker->sx < 0)
				{
					shaker->sx = graphics_variables.SCREEN_WIDTH;
				}

				if(shaker->sy > graphics_variables.SCREEN_LENGTH)
				{
					shaker->sy = 0;
				}
				else if(shaker->sy < 0)
				{
					shaker->sy = graphics_variables.SCREEN_LENGTH;
				}
		}while((shaker = shaker->next));
	}
}

int randint(int n)
{
  if((n-1) == RAND_MAX)
  {
    return rand();
  }
  else
  {
    long end = RAND_MAX/n;
    assert(end>0L);
    end *= n;

    int r;
    while((r = rand())>= end);
    return r%n;
  }
}
