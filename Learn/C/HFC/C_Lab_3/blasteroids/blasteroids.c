#include "blasteroids.h"

data_t0 graphics_variables;
data_t1 objects_variables;
control threads;
spaceship s;
blast b;

ALLEGRO_TIMER *timer;
ALLEGRO_EVENT event;

int main(int argc, char **argb)
{
	if(!al_init())
		error("Could not initialise Allegro5!\n");
// Set thread control data
	threads.doexit = false;
	threads.redraw = false;
	graphics_variables.myself = &threads;
	objects_variables.myself = &threads;
	graphics_variables.display_p = NULL;
	objects_variables.do_turn_left = false;
	objects_variables.do_turn_right = false;
	objects_variables.do_accelerate = false;
	objects_variables.do_decelerate = false;

// Create and start threads
	ALLEGRO_THREAD *t0 = al_create_thread(graphics,(void *)&graphics_variables);
	ALLEGRO_THREAD *t1 = al_create_thread(objects, (void *)&objects_variables);
	if(t0 == NULL || t1 == NULL)
		error("Could not create thread(s)");
	al_start_thread(t0);
	al_start_thread(t1);
	
// Start the timer and keyboard communications
	timer = al_create_timer(1.0/FPS);
	if(!timer)
		error("Could not create timer");
	al_start_timer(timer);	
	
	if(!al_install_keyboard())
		error("Could not install keyboard");

// Create an event queue and register all sources with it.
	ALLEGRO_EVENT_QUEUE *queue;
	ALLEGRO_EVENT event;
	queue = al_create_event_queue();
	//al_register_event_source(queue, al_get_display_event_source(graphics_variables.display_p));
	al_register_event_source(queue, al_get_timer_event_source(timer));
	al_register_event_source(queue, al_get_keyboard_event_source());

// Variables for direction keys. If a key is pressed, the respective variable is true
	enum MYKEYS {KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT};
	bool key[4] = {false, false, false, false};
	threads.no_events = false;
	
	while(!threads.doexit)
	{
		al_wait_for_event(queue, &event);
		
		if(event.type == ALLEGRO_EVENT_TIMER)
		{
			threads.redraw = false;
			if(key[KEY_UP])
			{
				objects_variables.do_accelerate = true;
			}
			else if(key[KEY_DOWN])
			{
				objects_variables.do_decelerate = true;
			}
			else if(key[KEY_LEFT])
			{
				objects_variables.do_turn_left = true;
			}
			else if(key[KEY_RIGHT])
			{
				objects_variables.do_turn_right = true;
			}
			else
			{
				objects_variables.do_accelerate = false;
				objects_variables.do_decelerate = false;
				objects_variables.do_turn_left = false;
				objects_variables.do_turn_right = false; 
			}
			threads.redraw = true;
		}
		else if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		{
			break;
		}
		else if(event.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			switch(event.keyboard.keycode)
			{
				case ALLEGRO_KEY_UP:
				key[KEY_UP] = true;
				break;
				
				case ALLEGRO_KEY_DOWN:
				key[KEY_DOWN] = true;
				break;
				
				case ALLEGRO_KEY_LEFT:
				key[KEY_LEFT] = true;
				break;
				
				case ALLEGRO_KEY_RIGHT:
				key[KEY_RIGHT] = true;
				break;
			}
		}
		else if(event.type == ALLEGRO_EVENT_KEY_UP)
		{
			switch(event.keyboard.keycode)
			{
				case ALLEGRO_KEY_UP:
				key[KEY_UP] = false;
				break;
				
				case ALLEGRO_KEY_DOWN:
				key[KEY_DOWN] = false;
				break;
				
				case ALLEGRO_KEY_LEFT:
				key[KEY_LEFT] = false;
				break;
				
				case ALLEGRO_KEY_RIGHT:
				key[KEY_RIGHT] = false;
				break;
				
				case ALLEGRO_KEY_ESCAPE:
				threads.doexit = true;
				break;
				
				case ALLEGRO_KEY_SPACE:
				create_blast(&s);
				break;
			}
		}
	}
	
	void **result;
	al_join_thread(t0, result);
	al_join_thread(t1, result);
	al_uninstall_system();
	return 0;
}

void *graphics(ALLEGRO_THREAD *thread, void *vars)
{
	data_t0 *graph_vars = (data_t0 *) vars;
	graph_vars->SCREEN_WIDTH = 1920;
	graph_vars->SCREEN_LENGTH = 1080;
	
	graph_vars->display_p = al_create_display(graph_vars->SCREEN_WIDTH, graph_vars->SCREEN_LENGTH);
	
	while(!threads.doexit)
	{
		if(threads.redraw)
		{
			al_clear_to_color(al_map_rgb(0, 0, 0));
			draw_spaceship(objects_variables.s_p);
			draw_blasts();
			al_flip_display();
		}
	}
	al_destroy_display(graph_vars->display_p);
	return NULL;
}

void *objects(ALLEGRO_THREAD *thread, void *objects_variables)
{	
	data_t1 *obj_vars = (data_t1 *) objects_variables;

	s.sx = graphics_variables.SCREEN_WIDTH/2;
	s.sy = graphics_variables.SCREEN_LENGTH/2;
	s.color = al_map_rgb(0, 255, 0);
	s.gone = false;
	s.current.speed = 0;
	s.current.allegro_degrees = 0;
	obj_vars->s_p = &s;
	
	while(!threads.doexit)
	{
		if(threads.redraw == true)
		{
			threads.redraw = false;
			if(obj_vars->do_turn_right)
				increase_angle(&s);
			else if(obj_vars->do_turn_left)
				decrease_angle(&s);
			else if(obj_vars->do_accelerate)
				accelerate_spaceship(&s);
			else if(obj_vars->do_decelerate)
				decelerate_spaceship(&s);
			move_spaceship(&s);
			manage_blasts();
		}
	}
	return NULL;
}

void error(char *msg)
{
	fprintf(stderr, "%s %s", msg, strerror(errno));
	exit(-1);
}
