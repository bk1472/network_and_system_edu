// socket
// connect
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/select.h>

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
	
	fd_set readfds;
	FD_ZERO(&readfds);
	FD_SET(0, &readfds);
	FD_SET(csock, &readfds);

	char buf[512];
	while (1)
	{
		fd_set rreadfds = readfds;
		int nfds = csock + 1;
		int ret = select(nfds, &rreadfds, 0, 0, 0);
		if (ret == 0)
			continue;

		if (FD_ISSET(0, &rreadfds))
		{
			int len = read(0, buf, sizeof buf);
			if (len == 0)
				break;
			
			write(csock, buf, len);
		}

		if (FD_ISSET(csock, &rreadfds))
		{
			int len = read(csock, buf, sizeof buf);
			if (len == 0)
				break;

			write(1, buf, len);
		}
	}

	close(csock);
}
