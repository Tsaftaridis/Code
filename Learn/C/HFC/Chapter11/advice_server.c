#include <stdio.h>

int main(int argc, char* argv)
{
	char *advice[] = 
	{
		"Take smaller bites\r\n",
		"Go for the tight jeans. They do NOT make you look fat.\r\n",
		"Just for today, be honest. Tell your boss what you *really* think\r\n",
		"You might want to rethink that haircut\r\n"
	};
	
	int listener_d = ................(PF_INET, SOCK_STREAM, 0);
	
	struct sockaddr_in name;
	name.sin_family = PF_INET;
	name.sin_port = (in_port_t)htons(30000);
	name.sin_addr.s_addr = htonl(INADDR_ANY);
}