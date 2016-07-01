//TODO: Figure out the #ifndef header game

// alpha_order fn: Sorts in alphabetical order an array of strings.
// -- Arguments: an array of strings(list), the number of elements in the list,
// 	  a pointer to a comparator function.
// -- Return type: void
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ 
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// list of function declarations
int compare_names(const void* a, const void* b);
void alpha_order(char** list, int num_of_elements, int (*comparator)(const void* a, const void* b));
int compare_names_desc(const void* a, const void* b);

// Sorting function - usable
void alpha_order(char** list, int num_of_elements, int (*comparator)(const void* a, const void* b))
{
	comparator = compare_names;
	//comparator = compare_names_desc;
	// Quicksorting (Uncomment above line to change comparator fn)
	qsort(list, num_of_elements, sizeof(char*), comparator);
}

// Comparator function for alphabetical order
int compare_names(const void* a, const void* b)
{
	char** name_a = (char**)a;
	char** name_b = (char**)b;
	return strcmp(*name_a, *name_b);
}

// Comparator function for inverse alphabetical order
int compare_names_desc(const void* a, const void* b)
{
	char** name_a = (char**)a;
	char** name_b = (char**)b;
	return strcmp(*name_b, *name_a);
}

