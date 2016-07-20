#include <stdio.h>
#include <signal.h>
#include "network.h"
#include "handler.h"

int listener_d;

void handle_shutdown(int sig)
{
	if(listener_d)
		close(listener_d);
	
	fprintf(stderr, "\nBye!\n");
	exit(0);
}

int main()
{
	if(catch_signal(SIGINT, handle_shutdown) == -1)
		error("Couldn't catch signal: ");
	
	listener_d = open_listener_socket();
	
	bind_to_port(listener_d, 30000);
	
	if(listen(listener_d, 10) == -1)
		error("Can't listen");
		
	struct sockaddr_storage client_addr;
	unsigned int address_size = sizeof(client_addr);
	char buffer[255];

	
	puts("Running");
	
	while(1)
	{	
		int connect_d = accept(listener_d, (struct sockaddr*)&client_addr, &address_size);
		
		if(connect_d == -1)
			error("Can't open secondary socket: ");
		
		if(say(connect_d, "Knock, knock!\r\n") != -1)
		{
			read_in(connect_d, buffer, sizeof(buffer));
			if(strncasecmp("Who's there?", buffer, 12))
			{
				say(connect_d, "You should say 'Who's there?'\r\n");	
			}
			else
			{
				if(say(connect_d, "Oscar\r\n") != -1)
				{
					read_in(connect_d, buffer, sizeof(buffer));
					if(strncasecmp("Oscar who?", buffer, 10))
					{
						say(connect_d, "You should say 'Oscar who?'\r\n");
					}
					else
					{
						say(connect_d, "Oscar silly question, you get a silly answer.\r\n");
					}
				}
			}
		}
		close(connect_d);
	}
	return 0;
}