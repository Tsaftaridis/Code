#include "final.h"

int main()
{
	// Get filenames and create the islands
	island *start = NULL;
	island *next = NULL;
	island *i = NULL;
	char name[80];
	
	for(; fgets(name, 80, stdin) != NULL; i = next)
	{
		next = create(name);
		if(start == NULL)
		{
			start = next;
		}
		
		if(i != NULL)
		{
			i->next = next;
		}
	}
		
	// Display the tour
	display(start);
	// Release memory
	release(start);
	// Exit
	return 0;
}

island* create(char *name)
{
	island  *p = malloc(sizeof(island));
	p->name = strdup(name);
	p->opens = "09:00";
	p->closes = "17:00";
	p->next = NULL;
	return p;
}

void display(island *i)
{
	for(; i != NULL; i=i->next)
	{
		printf("Name: %s Open: %s-%s\n\n", i->name, i->opens, i->closes);
	}
}

void release(island *start)
{
	island *next = NULL;
	island *i = start;
	for(; i != NULL; i = i->next)
	{
		next = i->next;
		free(i->name);
		free(i);
	}
}