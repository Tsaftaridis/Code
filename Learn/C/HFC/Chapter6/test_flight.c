#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct island{
	char *name;
	char *opens;
	char *closes;
	struct island *next;
}island;

island* create(char *name);
void display(island *start);

int main()
{
	char name[80];
	fgets(name, 80, stdin);
	island *p_island0 = create(name);
	fgets(name, 80, stdin);
	island *p_island1 = create(name);
	
	display(p_island0);
	display(p_island1);
	
	return 0;
}

island* create(char *name)
{
	island *i = malloc(sizeof(island));
/** 
  * Look at the line with "i->name". Instead of passing the pointer "name" itself to 
  * "i->name", which would give us just a new pointer pointing at the old string (which
  * pointer would be stored in the heap, but the string itself would be stored in the
  * stack, with all the other variables from main), we store a copy of the string in 
  * the heap to
  * ensure that the contents of the name string have the same lifespan as the struct 
  * we are creating. That means that the contents of the "name" pointer will not be
  * changed once we reuse the "name" variable in 'main', to name the second island.
  *
  **/
	i->name = strdup(name);
	i->opens = "09:00";
	i->closes = "17:00";
	i->next = NULL;
	return i;
}

void display(island *start)
{
	island *i = start;
	for (; i != NULL; i = i->next)
	{
		printf("Name: %s, opens: %s, closes: %s\n", i->name, i->opens, i->closes);
	}
}