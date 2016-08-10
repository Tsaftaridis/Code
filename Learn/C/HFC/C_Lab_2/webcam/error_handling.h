#include <stdio.h>
#include <errno.h>
#include <string.h>

void error(char* msg)
{
	printf("%s: %s", msg, strerror(errno));
	exit(errno);
}