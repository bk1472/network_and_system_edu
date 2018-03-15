// socket
// connect
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#include <stdio.h>
#include <poll.h>

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
	struct pollfd fds[2];
	fds[0].fd = 0;
	fds[0].events = POLLIN;
	fds[1].fd = csock;
	fds[1].events = POLLIN;

	char buf[512];
	while (1)
	{
		int ret = poll(fds, 2, -1);
		if (ret == 0)
			continue;

		if (fds[0].revents & POLLIN)
		{
			int len = read(0, buf, sizeof buf);
			write(csock, buf, len);
		}

		if (fds[1].revents & POLLIN)
		{
			int len = read(csock, buf, sizeof buf);
			if (len <= 0)
				break;

			write(1, buf, len);
		}
	}

	close(csock);
}
