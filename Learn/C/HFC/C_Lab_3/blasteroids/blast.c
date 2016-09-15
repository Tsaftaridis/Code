#include <math.h>
#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>

#include "blast.h"

#ifndef PI
#define PI 3.14
#endif

#ifndef RADIANS
#define RADIANS(x)  x*PI/128
#endif

float SCREEN_W;

static blast *head = NULL;
static blast *conductor = NULL;
static blast *painter = NULL;
static blast *mover = NULL;
static blast *hitter = NULL;

int BLAST_NUM = 0;

void draw_blasts()
{
	if(head)
	{
		painter = head;
		do
		{
			if(painter->gone == 0)
			{
				ALLEGRO_TRANSFORM t;
				al_identity_transform(&t);
				al_translate_transform(&t, painter->sx, painter->sy);
				al_use_transform(&t);
				float adjust = 0.5*SCREEN_W/1080;
				al_draw_line(0, 0, 1*adjust, 12*adjust, painter->color, adjust*10.0f);
			}
		}while((painter = painter->next));
	}
}

void move_blast()
{
	if(head)
	{
		mover = head;
		do
		{
			float rad = RADIANS(mover->heading);
			mover->sy = mover->sy - mover->speed * cos(rad);
			mover->sx = mover->sx + mover->speed * sin(rad);

			if(mover->sx < 0 || mover->sx > 1920 || mover->sy > 1080 || mover->sy < 0)
			{
				mover->gone = 1;
			}
		}while((mover = mover->next));
	}
}

void create_blast(spaceship *s)
{
	spaceship* mothership = s;
	if(!head && mothership)
	{
		head = malloc(sizeof(struct blast));
		head->sx = mothership->sx;
		head->sy = mothership->sy;
		head->heading = mothership->current.allegro_degrees;
		head->speed = 30;
		head->gone = 0;
		head->color = al_map_rgb(255, 255, 255);
		head->next = NULL;
	}
	else if(head && mothership)
	{
		conductor = head;
		while(conductor->next)
		{
			conductor = conductor->next;
		}
		conductor->next = malloc(sizeof(struct blast));
		conductor = conductor->next;

		if(conductor == NULL)
		{
			printf("Out of memory!\n");
			exit(-2);
		}
		else
		{
			conductor->sx = mothership->sx;
			conductor->sy = mothership->sy;
			conductor->heading = mothership->current.allegro_degrees;
			conductor->speed = 30;
			conductor->gone = 0;
			conductor->color = al_map_rgb(255, 255, 255);
			conductor->next = NULL;
		}
	}
	BLAST_NUM++;
}


void manage_blasts()
{
	int i = 0, j = 0;
	conductor = head;
	blast* prev = NULL;
	prev = head;
	while(conductor)
	{
		if(conductor->gone == 0)
		{
			blast_coordinates[i][j] = conductor->sx;
			blast_coordinates[i][j+1] = conductor->sy;
			prev = conductor;
		}
		else if(conductor->gone == 1)
		{
			if(conductor->next)
			{
				if(conductor == head)
				{
					blast *del = head;
					head = head->next;
					del = conductor;
					conductor = head;
					free(del);
					BLAST_NUM--;
				}
				else
				{
					blast *del = NULL;
					prev->next = conductor->next;
					del = conductor;
					conductor = prev;
					free(del);
					BLAST_NUM--;
				}
			}
			else
			{
				if(conductor == head)
				{
					head = NULL;
					free(conductor);
					BLAST_NUM--;
					conductor = NULL;
				}
			}
		}
		if(conductor && conductor->next)
			conductor = conductor->next;
		else
			break;
		i++;
	}
	move_blast();
}

// Removes blasts that have hit an asteroid
void blast_hit(int blast_num)
{
	int i;
	hitter = head;
	// Move to the n'th blast (starting from 0)
	for(i = 0; i < blast_num; i++)
	{
		hitter = hitter->next;
	}
	// Set it to be deleted
	hitter->gone = 1;
	hitter = NULL;
}

/*
void manage_blasts(int coordinates[20][2])
{
	//TODEB
	//Get the head and conductor;
	conductor = head;
	blast* prev = NULL;
	prev = head;
	// and while there are blasts
	while(conductor)
	{
		// If the blast exists, do nothing.
		if(conductor->gone == 0)
		{
			prev = conductor;
		}
		// If the blast does not exist,
		else if(conductor->gone == 1)
		{
			// delete it ./-prev->next = con->next-\.
			//     |--------|    |--------|   |--------|
			//     |  prev  |--> |temp/con|-->|con->nex|--> 0x0
			//     |________|    |________|   |________|
			// If there is a blasts after it
			if(conductor->next)
			{
				if(conductor == head)
				{
					// Temporary pointer for the struct that is to be deleted.
					blast *del = head;
			    	// Keep the chain closed
			    	// Set the first part of the chain's next pointer to the struct after the
			    	// one to be deleted.
					head = head->next;
					// Set the del pointer to the struct to be deleted
					del = conductor;
					// Take the conductor to the first part of the chain
					conductor = head;
					// Free the struct to be deleted
					free(del);
				}
				else
				{
					// Temporary pointer for the struct that is to be deleted.
					blast *del = NULL;
			    	// Keep the chain closed
			    	// Set the first part of the chain's next pointer to the struct after the
			    	// one to be deleted.
					prev->next = conductor->next;
					// Set the del pointer to the struct to be deleted
					del = conductor;
					// Take the conductor to the first part of the chain
					conductor = prev;
					// Free the struct to be deleted
					free(del);
				}
			}
			// If there are no blasts after it
			else
			{
				// And the conductor is not the head;************ ATTENTION ********* <<FIX THIS
				if(conductor == head)
				{
					head = NULL;
					free(conductor);
					conductor = NULL;
				}
				//else
				//{
				//	printf("Freed conductor");
				//	blast *del = NULL;
				//	del = conductor;
				//	conductor = prev;
					// Free it
				//	free(del);
				//}
			}
		}

		// If there is another blast move to it.
		if(conductor && conductor->next)
			conductor = conductor->next;
		// Otherwise, exit.
		else
			break;
	}
	move_blast();
}*/
