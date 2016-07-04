#include <stdio.h>

enum response_type {DUMP, SECOND_CHANCE, MARRY, LAW_SUIT};

// Matching name to response type.
typedef struct 
{
	char* name;
	enum response_type type;
}response;

// Creating the fns that will output based on the name and response type.
void dump(response r)
{
	printf("Dear %s,\n", r.name);
	puts("Unfortunately your last date contacted us to");
	puts("say that they will not be seeing you again");
}


void law_suit(response r)
{
	printf("Dear %s,\n", r.name);
	puts("Unfortunately you last date has contacted us");
	puts("to say that they are filing a law suit against you.");
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

// ARRAY OF FUNCTIONS
// Will be used to simplify the code.
// You can use the index 0, 1, 2 function depending on the enum response_type.
// So, if you have a DUMP, with an index of 0, you will get the 0'th function
// from the array, which gives you dump.
// SYNTAX: return type 			(*pointer_name[])		(parameter type)
// 			^(needs to be same)				  ^^(it's an array)	^(needs to be same)
void (*replies[])(response) = {dump, second_chance, marry, law_suit}; 

int main()
{
	response r[] = {{"Murdock", DUMP}, {"Foggy", SECOND_CHANCE}, {"Karen", SECOND_CHANCE}, 
	{"Vanessa", MARRY}, {"Wilson", LAW_SUIT}};
	
	int i;
	for(i = 0; i < 5; i++)
	{
	// Difference from the redundant code
		replies[r[i].type](r[i]);
	}
	return 0;
}
