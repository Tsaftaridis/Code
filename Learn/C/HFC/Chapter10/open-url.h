#include <stdio.h>
#include <unistd.h>
#include "error_handling.h"

void open_url(char* url)
{	
	pid_t pid = fork();
	
	if(!pid)
	{
		if(execlp("open", "open", url, NULL) == -1)
			error("No response for mac...");
		else if(execlp("x-www-browser", "x-www-browser", url, "&", NULL)== -1)
			error("No response for linux...");
		else if(execlp("cmd", "cmd", "/c", "start", url, NULL) == -1)
			error("No response for Windows...\nSomething must be wrong.");
	}
}