#include "blasteroids.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <pthread.h>
#include <signal.h>
// Convert degrees in allegro degrees (know the input in deg).
#define DEGREES_TO_AL(x) (float)((x)*12.4/180)

// Convert allegro degrees in degrees (need the output in deg).
#define AL_TO_DEGREES(x) (float)((x)*180/12.4)


typedef struct ALLEGRO_DISPLAY ALLEGRO_DISPLAY;
typedef struct ALLEGRO_COND ALLEGRO_COND;

const float FPS = 60;
const int SCREEN_W = 1920;
const int SCREEN_L = 1080;

ALLEGRO_EVENT event;
enum MYKEYS {KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT};

spaceship s;

int main(int argc, char **argv)
{
	ALLEGRO_EVENT_QUEUE *queue = NULL;
	ALLEGRO_EVENT event;
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_TIMER *timer = NULL;
	bool redraw = true;
	bool doexit = false;
	bool key[4] = {false, false, false, false};
	
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
	s.sx = 960;
	s.sy = 540;
	s.current.angle = 0;
	s.old.angle = 0;
	
	al_register_event_source(queue, al_get_display_event_source(display));
	al_register_event_source(queue, al_get_timer_event_source(timer));
	al_register_event_source(queue, al_get_keyboard_event_source());
 	al_clear_to_color(al_map_rgb(0,0,0));
 	al_flip_display();
 	al_start_timer(timer);

	while(!doexit)
	{	
		al_clear_to_color(al_map_rgb(0,0,0));
		draw_spaceship(&s);
		al_flip_display();
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
				s.current.angle -= 0.9;
			}
			
			else if(key[KEY_RIGHT])
			{
				s.current.angle += 0.9;
				
			}
			move_spaceship(&s);
			redraw = true;
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
				doexit = true;
				break;
			}
		}
		
		if(redraw && al_is_event_queue_empty(queue))
		{
			redraw = false;
			
			al_clear_to_color(al_map_rgb(0, 0, 0));
			
			draw_spaceship(&s);
			
			al_flip_display();
		}

	}
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

void error(char* msg)
{
	fprintf(stderr, "%s %s", msg, strerror(errno));
}
