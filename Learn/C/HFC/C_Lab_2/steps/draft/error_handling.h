#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

void error(char* msg)
{
	fprintf(stderr, "%s: %s", msg, strerror(errno));
	exit(1);
}