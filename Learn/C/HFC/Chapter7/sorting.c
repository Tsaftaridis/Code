#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int compare_scores(const void* score_a, const void* score_b)
{
	int a = *(int*) score_a;
	int b = *(int*) score_b;
	return a-b;
}

int compare_scores_desc(const void* score_a, const void* score_b)
{
	int a = *(int*) score_a;
	int b = *(int*) score_b;
	return b-a;
}

typedef struct
{
	int width;
	int length;
}rectangle;

int compare_areas(const void* a, const void* b)
{
	rectangle* rect_a = (rectangle*)a;
	rectangle* rect_b = (rectangle*)b;
	int area_a = (rect_a->width) * (rect_a->length);
	int area_b = (rect_b->width) * (rect_b->length);
	return area_a - area_b; 
}

int compare_names(const void* a, const void* b)
{
	char** name_a = (char**)a;
	char** name_b = (char**)b;
	return strcmp(*name_a, *name_b);
}

int compare_areas_desc(const void* a, const void* b)
{
	return compare_names(b, a);	
}

int compare_names_desc(const void* a, const void* b)
{
	return compare_names(b, a);
}

int main()
{
	int scores[] = {543, 323, 32, 554, 11, 3, 112};
	int i;
	qsort(scores, 7, sizeof(int), compare_scores_desc);
	puts("These are the scores in descending order:");
	for(i = 0; i < 7; i++)
	{
		printf("%d\n", scores[i]); 
	}
	
	char* names[] = {"Karen", "Murdoc", "Foggy", "Wilson"};
	qsort(names, 4, sizeof(char*), compare_names);
	puts("\nThese are the names in alphabetical order:");
	for(i = 0; i < 4; i++)
	{
		printf("%s\n", names[i]);
	}
	return 0;
}