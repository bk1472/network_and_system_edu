// socket
// connect
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
	
	if (connect(csock, (struct sockaddr*)&saddr, sizeof saddr) == -1)
	{
		perror("connect");
		return -1;
	}

	printf("connected...\n");

	char buf[512];
	int len;
	while ((len = read(0, buf, sizeof buf)) > 0)
	{
		if (write(csock, buf, len) == -1)
		{
			perror("write");
			break;
		}

		len = read(csock, buf, sizeof buf);
		if (len == 0)
			break;
		else if (len == -1)
		{
			perror("read");
			break;
		}

		write(1, buf, len);
	}

	close(csock);
}
