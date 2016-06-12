#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct island 
{
	char* name;
	char* opens;
	char* closes;
	struct island *next;
}island;

void display(island *i);

island* create(char* name);

void release (island *start);