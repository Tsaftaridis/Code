#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include "error_handling.h"


int main(int argc, char* argv[])
{
	char* phrase = argv[1];
	char* vars[] = {"RSS_FEED=http://rss.cnn.com/rss/cnn_topstories.rss", NULL};
	FILE *f = fopen("stories.txt", "w");
	if(!f)
	{
		error("Can't open file 'stories.txt'");
	}
	
	pid_t pid = fork();
	if(pid == -1)
		error("Can't fork process");

	if(!pid)
	{
		if(dup2(fileno(f), 1) == -1)
			error("Can't redirect Standard Output");
		if(execle("/usr/local/bin/python2", "usr/local/bin/python2", "rssgossip.py", phrase, NULL, vars) == -1)
			error("Can't run script");
	}
	
	int pid_status;
	if(waitpid(pid, &pid_status, 0) == -1)
		error("Error waiting for child process");
	
	return 0;
}