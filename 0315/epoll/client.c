// socket
// connect
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/epoll.h>
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

	int efd = epoll_create1(0);
	if (efd == -1)
	{
		perror("epoll_create1");
		return -1;
	}

	struct epoll_event events[] = {
		{
			.events = EPOLLIN,
			.data.fd = 0
		},
		{
			.events = EPOLLIN,
			.data.fd = csock
		}
	};

	for (int i = 0 ; i < 2 ; ++i)
		epoll_ctl(efd, EPOLL_CTL_ADD, events[i].data.fd, &events[i]);

	char buf[512];
	struct epoll_event revents[2];
	int finish = 0;
	while (1)
	{
		int n = epoll_wait(efd, revents, 2, -1);
		if (n == 0)
			continue;

		for (int i = 0 ; i < 2 ; ++i)
		{
			if (revents[i].data.fd == 0)
			{
				int len = read(0, buf, sizeof buf);
				if (len <= 0)
				{
					finish = 1;
					break;
				}

				write(csock, buf, len);
			}
			else 
			{
				int len = read(csock, buf, sizeof buf);
				if (len <= 0)
				{
					close(csock);
					finish = 1;
					break;
				}

				write(1, buf, len);
			}
		}

		if (finish)
			break;
	}

}








