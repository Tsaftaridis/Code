#include <math.h>
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

static blast *head = NULL;
static blast *conductor = NULL;
static blast *painter = NULL;
static blast *mover = NULL;

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
				al_draw_line(0, 0, 1, 12, painter->color, 10.0f);
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
}

void manage_blasts()
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
}
