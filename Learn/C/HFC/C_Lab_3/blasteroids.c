#include "blasteroids.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <pthread.h>
#include <signal.h>
#include <math.h>

typedef struct ALLEGRO_DISPLAY ALLEGRO_DISPLAY;
typedef struct ALLEGRO_COND ALLEGRO_COND;

const float FPS = 60;
const int SCREEN_W = 1920;
const int SCREEN_L = 1080;
ALLEGRO_TIMER *timer;
ALLEGRO_DISPLAY *display;


ALLEGRO_EVENT event;
enum MYKEYS {KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT, KEY_SPACE};

spaceship s;

typedef struct data
{
	ALLEGRO_DISPLAY *display;
	bool redraw;
	bool doexit;
	bool empty_queue;
}data;
	

void* keys(ALLEGRO_THREAD* a, void* data_t0)
{
	printf("Running t0\n");
	data* variables = (data*)data_t0;
	ALLEGRO_EVENT_QUEUE *queue = NULL;
	ALLEGRO_EVENT event;
	
	timer = al_create_timer(1.0/FPS);
	if(!timer)
		error("Could not create timer.");
		
	if(!al_install_keyboard())
		error("Could not install keyboard");
	
	(variables->doexit) = false;
	bool key[5] = {false, false, false, false, false};
	queue = al_create_event_queue();
	al_start_timer(timer);
	al_register_event_source(queue, al_get_display_event_source(variables->display));
	al_register_event_source(queue, al_get_timer_event_source(timer));
	al_register_event_source(queue, al_get_keyboard_event_source());

	while(!(variables->doexit))
	{
		al_wait_for_event(queue, &event);
		if(event.type == ALLEGRO_EVENT_TIMER)
		{
			if(key[KEY_UP])
			{
				accelerate_spaceship(&s);
			}
			
			else if(key[KEY_DOWN])
			{
				decelerate_spaceship(&s);
			}
			
			else if(key[KEY_LEFT])
			{	
					s.current.allegro_degrees -= 1;
			}
			
			else if(key[KEY_RIGHT])
			{
				s.current.allegro_degrees += 1;
			}
			else if(key[KEY_SPACE])
			{
				key[KEY_SPACE] = false;
				create_blast(&s);
				destroy_blasts();
			}
			variables->redraw = true;
		}
		
		else if(event.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			switch(event.keyboard.keycode)
			{
				case ALLEGRO_KEY_LEFT:
				key[KEY_LEFT] = true;
				break;
				case ALLEGRO_KEY_RIGHT:
				key[KEY_RIGHT] = true;
				break;
				case ALLEGRO_KEY_UP:
				key[KEY_UP] = true;
				break;
				case ALLEGRO_KEY_DOWN:
				key[KEY_DOWN] = true;
				break;
				case ALLEGRO_KEY_SPACE:
				key[KEY_SPACE] = true;
				break;
			}
		}
		
		else if(event.type == ALLEGRO_EVENT_KEY_UP)
		{
			switch(event.keyboard.keycode)
			{
				case ALLEGRO_KEY_LEFT:
				key[KEY_LEFT] = false;
				break;
				case ALLEGRO_KEY_RIGHT:
				key[KEY_RIGHT] = false;
				break;
				case ALLEGRO_KEY_UP:
				key[KEY_UP] = false;
				break;
				case ALLEGRO_KEY_DOWN:
				key[KEY_DOWN] = false;
				break;
				case ALLEGRO_KEY_ESCAPE:
				(variables->doexit) = true;
				break;
			}
		}
		if(al_is_event_queue_empty(queue) && variables->redraw)
		{
			move_spaceship(&s);
			move_blast();
		}
	}
	al_destroy_event_queue(queue);
	return NULL;
}

void* painter(ALLEGRO_THREAD* b, void* data_t0)
{
	printf("\nRunning t1");
	data* variables = (data*) data_t0;

	while(!variables->doexit)
	{
		usleep(3000);
	}
	return NULL;
}

int main(int argc, char **argv)
{	
	// Initialise allegro framework
	if(!al_init())
		error("Could not install allegro system.");

	//Create a display
	display = al_create_display(SCREEN_W, SCREEN_L);
	
	if(!display)
	{
		al_destroy_timer(timer);
		error("Could not create display...");
	}

	// Change display
	s.color = al_map_rgb(0, 255, 0);
	s.sx = 960;
	s.sy = 540;
	s.current.allegro_degrees = 0;
	s.old.allegro_degrees = 0;

	data data_t0 = {display, false, false, true};

	ALLEGRO_THREAD *t1 = al_create_thread(painter, (void*)&data_t0);
	if(t1 == NULL)
		error("Could not create thread t1");
	al_start_thread(t1);

 	ALLEGRO_THREAD *t0 = al_create_thread(keys, (void*)&data_t0);
	if(t0 == NULL)
		error("Could not create thread t0");
	al_start_thread(t0);
	
	while(!data_t0.doexit)
	{
		if(data_t0.redraw)
		{
			al_clear_to_color(al_map_rgb(0,0,0));
			draw_spaceship(&s);
			draw_blasts();
			al_flip_display();
		}
	}
	
	void **result;
	al_join_thread(t1, result);
	al_join_thread(t0, result);

	al_destroy_display(display);
	al_uninstall_system();
	return 0;
}

// Detects collisions and does stuff...
void collision()
{
	// TODO
}

void error(char* msg)
{
	fprintf(stderr, "%s %s", msg, strerror(errno));
	exit(-1);
}