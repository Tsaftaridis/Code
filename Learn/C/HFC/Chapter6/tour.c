#include <stdio.h>

// On the *next line, island *next wouldn't have worked. You can't use the alias and have
// to give the struct a proper name.
typedef struct island 
{
	char *name;
	char *opens;
	char *closes;
	struct island *next;	
}island;

void display(island *start);

int main()
{
	island amity = {"Amity", "09:00", "17:00", NULL};
	island craggy = {"Craggy", "09:00", "17:00", NULL};
	island isla_nublar = {"Isla Nublar", "09:00", "17:00", NULL};
	island shutter = {"Shutter", "09:00", "17:00", NULL};
	island skull  = {"Skull", "09:00", "17:00", NULL};
	
	amity.next = &craggy;
	craggy.next = &isla_nublar;
	isla_nublar.next = &skull;
	skull.next = &shutter;
	
	display(&amity);
	
	return 0;
}

void display(island *start)
{
	island *i = start;
	for (; i != NULL; i = i->next)
	{
		printf("Name: %s, opens: %s, closes: %s\n", i->name, i->opens, i->closes);
	}
}