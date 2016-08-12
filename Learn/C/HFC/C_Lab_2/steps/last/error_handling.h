#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

void error(char* msg)
{
	printf("%s: %s", msg, strerror(errno));
	exit(0);
}