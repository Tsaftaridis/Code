#include "blasteroids.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <pthread.h>
#include <signal.h>

typedef struct ALLEGRO_DISPLAY ALLEGRO_DISPLAY;
typedef struct ALLEGRO_COND ALLEGRO_COND;

const float FPS = 60;
const int SCREEN_W = 640;
const int SCREEN_L = 480;

	ALLEGRO_EVENT event;

spaceship s;

int main(int argc, char **argv)
{
	ALLEGRO_EVENT_QUEUE *queue = NULL;
	ALLEGRO_EVENT event;
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_TIMER *timer = NULL;
	bool redraw = true;
	bool doexit = false;
	
	// Initialise allegro framework
	if(!al_init())
		error("Could not install allegro system.");
	
	if(!al_install_keyboard())
		error("Could not install keyboard");
		
	timer = al_create_timer(1.0/FPS);
	if(!timer)
		error("Could not create timer.");
	//Create a display
	display = al_create_display(SCREEN_W, SCREEN_L);
	
	if(!display)
	{
		al_destroy_timer(timer);
		error("Could not create display...");
	}

	queue = al_create_event_queue();	
	
	// Change display
	s.color = al_map_rgb(0, 255, 0);
	s.sx = 200;
	s.sy = 200;
	
	al_register_event_source(queue, al_get_display_event_source(display));
	al_register_event_source(queue, al_get_timer_event_source(timer));
	al_register_event_source(queue, al_get_keyboard_event_source());
 	al_clear_to_color(al_map_rgb(0,0,0));
 	al_flip_display();
 	al_start_timer(timer);
	ALLEGRO_THREAD *t0 = al_create_thread(keys, NULL);
	if(t0 == NULL)
		error("Could not create thread t0");
		
	al_start_thread(t0);

	while(!doexit)
	{	
		al_clear_to_color(al_map_rgb(0,0,0));
		draw_spaceship(&s);
		al_flip_display();
		al_wait_for_event(queue, &event);
		if(event.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			switch(event.keyboard.keycode)
			{
				case ALLEGRO_KEY_LEFT:
				s.sx -= 10;
				break;
				case ALLEGRO_KEY_RIGHT:
				//TODO;
				break;
				case ALLEGRO_KEY_UP:
				//TODO;
				break;
				case ALLEGRO_KEY_DOWN:
				//TODO;
				break;
				case ALLEGRO_KEY_SPACE:
				raise(SIGINT);
				break;			
			}
		}

	}
	
	void **result;
	al_join_thread(t0, result);
	al_destroy_display(display);
	al_destroy_event_queue(queue);
	al_uninstall_system();
	
	return 0;
}

// Detects collisions and does stuff...
void collision()
{
	// TODO
}

//Waits for events and passes it onto handle_event
void* keys(ALLEGRO_THREAD* a, void* b)
{
	return NULL;
}

void error(char* msg)
{
	fprintf(stderr, "%s %s", msg, strerror(errno));
}
