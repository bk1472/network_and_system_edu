#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#include <stdio.h>

#include "packet.h"

int main()
{
	int csock = socket(PF_INET, SOCK_STREAM, 0);
	if (csock == -1)
	{
		perror("socket");
		return -1;
	}
	
	struct sockaddr_in saddr = {0, };
	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(5000);
	saddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	
	if (connect(csock, (struct sockaddr*)&saddr, sizeof saddr) == -1)
	{
		perror("connect");
		return -1;
	}

	printf("connected...\n");

	int lhs = 10, rhs = 32;
	char op = '+';
	// while (scanf("%d%c%d", &lhs, &op, &rhs) == 3)
	int i;
	for (i = 0 ; i < 10000; ++i)
	{
		char buf[512];
		Packet packet(buf);
		packet.writeByte(op);
		packet.writeInt32(lhs);
		packet.writeInt32(rhs);

		int len = packet.length();

		short packetlen = htons(len);
		write(csock, &packetlen, sizeof packetlen);

		for (int j = 0 ; j < len ; ++j)
		{
			write(csock, buf + j, 1);
			usleep(10);
		}
	}

	close(csock);
}




















