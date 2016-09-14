#ifndef DATA_STRUCTS
#define DATA_STRUCTS
typedef struct control
{
	bool doexit;
	bool redraw;
	bool no_events;
}control;

typedef struct data_t0
{
	control* myself;
	ALLEGRO_DISPLAY *display_p;
	int SCREEN_WIDTH;
	int SCREEN_LENGTH;
}data_t0;

extern int BLAST_NUM;
extern int NUM_OF_ASTEROIDS;
extern int asteroid_coordinates[10][2];
extern int blast_coordinates[20][2];

extern data_t0 graphics_variables;
#endif
