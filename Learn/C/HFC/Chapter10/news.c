#include <stdio.h>
#include <unistd.h>
#include "open-url.h"

int main()
{
	char* url = "http://rss.cnn.com/rss/cnn_topstories.rss";
	open_url(url);
}