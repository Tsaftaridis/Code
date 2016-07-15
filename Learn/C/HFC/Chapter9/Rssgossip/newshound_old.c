#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stduni.h>

int main(int argc, char *argv[])
{
	// The feeds to search through
	char* feeds = { "http://rss.cnn.com/rss/cnn_topstories.rss",
					"http://feeds.nytimes.com/nyt/rss/HomePage",
					"http://www.washingtonpost.com/rss/",
					"http://hosted.ap.org/lineups/USHEADS-rss_2.0.xml?SITE=RANDOM&SECTION=HOME",
					"http://rssfeeds.usatoday.com/usatoday-NewsTopStories",
					"http://www.npr.org/rss/rss.php?id=1001",
					"http://feeds.reuters.com/reuters/topNews",
					"http://newsrss.bbc.co.uk/rss/newsonline_world_edition/americas/rss.xml"
				  };
	int times = 8;
	
	// The search key
	char *phrase = argv[1];
	
	int i;
	// Loop through the feeds searching for the search key
	for(i = 0; i < times; i++)
	{
		char var[255];
		sprintf(var, "RSS_FEED=%s", feeds[i]);
		char *vars[] = {var, NULL};
		if(execle("usr/bin/python", "usr/bin/python", phrase, NULL, vars) == -1)
		// Error handling
		{
			fprintf(stderr, "Can't run script: %s\n", strerror(errno));
			return 1;
		}
	}
	return 0;
}