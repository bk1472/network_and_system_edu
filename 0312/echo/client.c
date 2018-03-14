#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#include <stdio.h>

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
	// loopback / localhost - 127.0.0.1

	int ret = connect(csock, (struct sockaddr*)&saddr, sizeof saddr);
	if (ret == -1)
	{
		perror("connect");
		return -1;
	}

	printf("connected...\n");
	getchar();

	close(csock);
}
