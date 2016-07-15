#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[])
{
	char *my_env[] = { NULL};
	if(execle("./coffee", "./coffee", argv[argc-1], NULL, my_env) == -1)
	{
		fprintf(stderr, "Can't run process 0: %s\n", strerror(errno));
		fprintf(stderr, "Can't create order: %s\n", strerror(errno));
		return 1;
	}
	return 0;		
}