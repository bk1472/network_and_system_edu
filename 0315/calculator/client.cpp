#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#include <stdio.h>
#include "calculator.pb.h"

ssize_t	readn(int fd, void *vptr, size_t n);

Request newRequest() 
{
	char ops[] = { '+', '*', '/' };

	Request req;
	req.set_lhs(rand() % 100);
	req.set_rhs(rand() % 100);
	req.set_op(ops[rand() % 3]);

	return req;
}

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

	struct epoll_event events[2];
	events[0].events = EPOLLIN;
	events[0].data.fd = 0;
	events[1].events = EPOLLIN;
	events[1].data.fd = csock;

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

				Request req = newRequest();
				len = req.ByteSize();
				short packetlen = htons(len);

				req.SerializeToArray(buf, len);
	
				write(csock, &packetlen, sizeof packetlen);
				write(csock, buf, len);
			}
			else 
			{
				short packetlen; 
				int len = readn(csock, &packetlen, sizeof packetlen);
				if (len <= 0)
				{
					printf("연결이 종료되었습니다.\n");
					close(csock);
					finish = 1;
					break;
				}

				packetlen = ntohs(packetlen);
				len = readn(csock, buf, packetlen);
				if (len <= 0)
				{
					printf("연결이 종료되었습니다.\n");
					close(csock);
					finish = 1;
					break;
				}

				Response res;
				res.ParseFromArray(buf, packetlen);
				printf("result: %ld\n", res.result());
			}
		}

		if (finish)
			break;
	}

}








