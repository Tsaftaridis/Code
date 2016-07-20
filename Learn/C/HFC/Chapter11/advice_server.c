#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#include "error_handling.h"

int main(int argc, char* argv[])
{
	char* advice[] = { 
					   "Take smaller bites\n", 
					   "Go for the tight jeans. They do NOT make you look fat.\n",
					   "One word: inappropriate.\r\n",
					   "Just for today, be honest. Tell your boss what you really think.\r\n",
 					   "You might want to rethink that haircut.\r\n"
					 };
				
	int listener_d;	 
	if((listener_d = socket(PF_INET, SOCK_STREAM, 0)) == -1)
		error("Can't create listening socket: ");
	
	struct sockaddr_in name;
	name.sin_family = PF_INET;
	name.sin_port = (in_port_t)htons(30000);
	name.sin_addr.s_addr = htonl(INADDR_ANY);
	
	if(bind(listener_d, (struct sockaddr*) &name, sizeof(name)) == -1)
		error("Can't bind to port: ");
	
	if(listen(listener_d, 10) == -1)
		error("Problem while listening: ");
	puts("Waiting for connection...");
	
	struct sockaddr_storage client_addr;
	unsigned int address_size = sizeof(client_addr);
	int connect_d;
	if((connect_d = accept(listener_d, (struct sockaddr *) &client_addr, &address_size)) == -1)
		error("Cannot accept connection:");
	
	char *msg = advice[rand() %5];
	
	send(connect_d, msg, strlen(msg), 0);
	close(connect_d);
	
	return 0;
}