#include <string.h>
#include <errno.h>

void error(char* msg)
{
	fprintf("%s: %s", msg, strerror(errno));
	exit(1);
}