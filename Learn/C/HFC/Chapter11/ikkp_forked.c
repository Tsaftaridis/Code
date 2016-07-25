#include <stdio.h>
#include <string.h>
#include "handler.h"
#include "network.h"

void handle_shutdown(int sig)
{
	fprintf(stderr, "\nBye!\n");
	exit(0);
}

int main()
{
	if(catch_signal(SIGINT, handle_shutdown) == -1)
		error("Could not handle signal");
	
	int listener_d = open_listener_socket();
	
	bind_to_port(listener_d, 30000);
	
	if(listen(listener_d, 10) == -1)
		error("Hearing problems");
		
	puts("\nWaiting, Seymour!\n");
	
	struct sockaddr_storage client_addr;
	unsigned int address_size = sizeof(client_addr);
	char buffer[255];
	
	while(1)
	{
		int connect_d = accept(listener_d, (struct sockaddr *)&client_addr, &address_size);
		
		if(connect_d == -1)
			error("Can't open secondary socket");
				
		if(!fork())
		{
			close(listener_d);
			
			if(say(connect_d, "Internet Knock-Knock server\r\nVersion 1.0\r\nKnock! Knock!\r\n>")
			 != -1)
			{
				read_in(connect_d, buffer, sizeof(buffer));
				
				if(strncasecmp("Who's there?", buffer, 12))
				{
					say(connect_d, "You should say 'Who's there?'\r\n>");
				}
				else
				{
					if(say(connect_d, "Oscar\r\n>") != -1)
					{
						read_in(connect_d, buffer, sizeof(buffer));
						
						if(strncasecmp("Oscar who?", buffer, 10))
						{
							say(connect_d, "You should say 'Oscar who?'\r\n>");
						}
						else
						{
							say(connect_d, "Oscar silly question, you get a silly answer\r\n>");
						}
					}
				}
			}
			close(connect_d);
			exit(0);
		}	
		close(connect_d);
	}
}