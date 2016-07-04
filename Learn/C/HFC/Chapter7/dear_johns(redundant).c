#include <stdio.h>

enum response_type {DUMP, SECOND_CHANCE, MARRY};

typedef struct 
{
	char* name;
	enum response_type type;
}response;

void dump(response r)
{
	printf("Dear %s,\n", r.name);
	puts("Unfortunately your last date contacted us to");
	puts("say that they will not be seeing you again");
}

void second_chance(response r)
{
	printf("Dear %s,\n", r.name);
	puts("Good news: your last date has asked us to");
	puts("arrange another meeting.");
}

void marry(response r)
{
	printf("Dear %s,\n", r.name);
	puts("Congratulations! Your last date has contacted");
	puts("us with a proposal of marriage!");
}

int main()
{
	response r[] = {{"Murdock", DUMP}, {"Foggy", SECOND_CHANCE}, {"Karen", SECOND_CHANCE}, 
	{"Wilson", MARRY}};

	int i;
	for(i = 0; i < 4; i++)
	{
		switch(r[i].type)
		{
			case DUMP:
			dump(r[i]);
			break;
			case SECOND_CHANCE:
			second_chance(r[i]);
			break;
			case MARRY:
			marry(r[i]);		
		}
	}
return 0;
}