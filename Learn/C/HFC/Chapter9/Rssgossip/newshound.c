#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	// The feeds to search through
	char* feeds[] = { "http://rss.cnn.com/rss/cnn_topstories.rss",
					"http://feeds.nytimes.com/nyt/rss/HomePage",
					"http://feeds.washingtonpost.com/rss/politics",
					"http://feeds.washingtonpost.com/rss/rss_arts-post",
					"http://feeds.washingtonpost.com/rss/entertainment",
					"http://feeds.washingtonpost.com/rss/opinions",
					"http://atwar.blogs.nytimes.com/feed/",
					"http://rss.nytimes.com/services/xml/rss/nyt/Soccer.xml"};
	int times = 8;
	
	// The search key
	char *phrase = argv[argc - 1];
	
	int i;
	// Loop through the feeds searching for the search key
	for(i = 0; i < times; i++)
	{
		char var[255];
		sprintf(var, "RSS_FEED=%s", feeds[i]);
		char *vars[] = {var, NULL};
		pid_t pid = fork();
		if( pid == -1)
		{
			fprintf(stderr, "Can't fork process: %s\n", strerror(errno));
			return 1;
		}
		if(!pid)
		{
			//Applications/Python 3.4/IDLE.app/Contents/MacOS/Python
			if(execle("/usr/local/bin/python2", "/usr/local/bin/python2", "rssgossip.py", phrase, NULL, vars) == -1)
			// Error handling
			{
				fprintf(stderr, "Can't run script: %s\n", strerror(errno));
				return 1;
			}
			return 0;
		}
	}
	return 0;
}