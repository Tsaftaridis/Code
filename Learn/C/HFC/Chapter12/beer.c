#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <errno.h>
#include "error_handling.h"

int beers = 2000000;

pthread_mutex_t beers_lock = PTHREAD_MUTEX_INITIALIZER;

void* drink_lots(void* a)
{
	int i;
	
	pthread_mutex_lock(&beers_lock);
	for(i = 0; i < 100000; i++)
	{
		beers = beers - 1;
	}
	printf("Beers = %i\n", beers);
	pthread_mutex_unlock(&beers_lock);

	return NULL;
}

int main()
{
	pthread_t threads[20];
	int t;
	printf("%i bottles of beer on the wall\n%i bottles of beer\n", beers, beers);
	for(t = 0; t < 20; t++)
	{
		if(pthread_create(&threads[t], NULL, drink_lots, NULL) == -1)
			error("Could not create thread");
	}
	
	void* result;
	for(t = 0; t < 20; t++)
	{
		pthread_join(threads[t], &result);
	}
	printf("There are now %i bottles of beer on the wall\n", beers);
	return 0;
}