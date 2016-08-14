#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <errno.h>
#include <string.h>

typedef struct ALLEGRO_COND ALLEGRO_COND;


ALLEGRO_DISPLAY *display = NULL;

void error(char* msg)
{
	fprintf(stderr, "%s %s", msg, strerror(errno));
	exit(1);
}

void* keys(ALLEGRO_THREAD* a, void* b)
{
	sleep(30);
	return NULL;
}


int main(int argc, char **argv)
{
	// Initialise allegro framework
	al_init();
	if(!al_is_system_installed())
		error("Could not fire allegro up");
	
	ALLEGRO_THREAD *t0 = al_create_thread(keys, NULL);
	if(t0 == NULL)
		error("Could not create thread t0");
	
	al_start_thread(t0);
	
	void **result;
	al_join_thread(t0, result);
	
	al_destroy_display(display);
	al_uninstall_system();
	return 0;
}