#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include "error_handling.h"

void open_url(char* url);

int main(int argc, char* argv[])
{
	char* phrase = argv[1];
	char* vars[] = {"RSS_FEED=http://rss.cnn.com/rss/cnn_topstories.rss", NULL};
	int fd[2];
	
	// Create a pipe w/ error handling
	if(pipe(fd) == -1)
		error("Can't create pipe");
	
	pid_t pid = fork();
	if(pid == -1)
	{
		error("Can't fork process.");
	}
	else if(!pid)
	{
		// Link f[1] (pipe input) to stdout of the child process (will write to pipe)
		// Close f[0] (won't read from pipe)
		dup2(fd[1], 1);
		close(fd[0]);
	}
	if(execle("/usr/local/bin/python", "usr/local/bin/python", "./rssgossip.py",
						"-u", phrase, NULL, vars) == -1)
	{
		error("Can't run script");
	}
	// Link f[0] (pipe output) to stdin (Will read from pipe)
	// Close f[1] (pipe input) (Won't write to pipe)
	dup2(fd[0], 0);
	close(fd[1]);
	
	char line[255];
	while(fgets(line, 255, stdin))
	{
		if(line[0] == '\t')
		// The string starting after the TAB character:
			open_url(line + 1);
	}
	
	return 0;
}


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