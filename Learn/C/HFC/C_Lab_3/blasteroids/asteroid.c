#include "asteroid.h"

#ifndef PI
#define PI 3.14
#endif

#ifndef RADIANS
#define RADIANS(x) (x)*PI/128
#endif

int NUM_OF_ASTEROIDS = 1;
int asteroid_coordinates[10][2];

float SCREEN_W, SCREEN_H;

asteroid *root = NULL;
asteroid *maestro = NULL;
asteroid *artist = NULL;
asteroid *shaker = NULL;
asteroid *breaker = NULL;

data_t0 graphics_variables;

void manage_asteroids()
{
	maestro = root;
	asteroid *prev = NULL;
	prev = root;
	int i = 0, j = 0;

	while(maestro)
	{
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
					NUM_OF_ASTEROIDS--;
					free(del);
				}
				else
				{
					asteroid *del = NULL;
					prev->next = maestro->next;
					del = maestro;
					maestro = prev;
					NUM_OF_ASTEROIDS--;
					free(del);
				}
			}
			else
			{
				if(maestro == root)
				{
					root = NULL;
					NUM_OF_ASTEROIDS--;
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
			// Change the graphics depending on the screen size(the originals were created for 1080p display)
			float change = SCREEN_H/1080;
			float s = artist->scale;
			s *= 2.5*change;
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
			// Variable to differenciate between asteroids that have been split alrdy.
			root->to_go = 0;
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
		maestro->to_go = 0;
	}
}

void initialize_asteroids()
{
	int i;
	for(i = 0; i < NUM_OF_ASTEROIDS; i++)
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

			// SCREEN_LENGTH ->|--------------------------|
			//								 |													|
			//								 |													|
			//								 |__________________________|
			//                 SCREEN_WIDTH-/
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

void asteroid_break(int n)
{
	if(root)
	{
		int i = 0;
		breaker = root;
		for(i = 0; i < n-1; i++)
		{
			breaker = breaker->next;
		}
		if(!breaker->to_go)
		{
			float start_point_x = breaker->sx;
			float start_point_y = breaker->sy;
			float start_point_heading = breaker->heading;
			float start_point_twist = breaker->twist;
			float start_point_speed = breaker->speed;

			breaker->scale = 0.5;
			breaker->heading += 20;
			breaker->ang_velocity *= 2;
			breaker->to_go = 1;

			create_asteroid();
			NUM_OF_ASTEROIDS++;
			// The asteroid created will be the last. Move to it and change the properties
			for(i = 0; i < NUM_OF_ASTEROIDS - n; i++)
			{
				breaker = breaker->next;
			}

			// The default scale is 1, so we change it by half
			breaker->scale = 0.5;
			// All the other data is created randomly in the create_asteroid function,
			// but we can change it immediately.
			breaker->sx = start_point_x;
			breaker->sy = start_point_y;
			breaker->speed = start_point_speed;
			breaker->twist = start_point_twist;
			breaker->ang_velocity *= -2;
			breaker->heading  = start_point_heading - 20;
			breaker->to_go = 1;

			breaker = NULL;
		}
		else
		{
			breaker->gone = 1;
			breaker = NULL;
		}
	}
}
