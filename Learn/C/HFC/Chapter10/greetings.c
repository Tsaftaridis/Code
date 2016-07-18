#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

void diediedie(int sig)
{
	puts(" Goodbye, cruel world...");
	exit(1);
}

int catch_signal(int signal, void (*handler)(int))
{
	struct sigaction action;
	action.sa_handler = handler;
	sigemptyset(&action.sa_mask);
	action.sa_flags = 0;
	// Register the sigaction with the OS, while giving the opportunity for error checking
	return sigaction(signal, &action, NULL);
}

int main()
{
	// Set up signal handling
	if(catch_signal(SIGINT, diediedie) == -1)
	{
		fprintf(stderr, "Could not setup signal handling");
		exit(2);
	}
	char name[30];
	printf("Enter your name:");
	fgets(name, 30, stdin);
	printf("Hello, %s\n", name);
	return 0;
}