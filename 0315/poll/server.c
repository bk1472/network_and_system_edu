#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#include <stdio.h>

// poll: System V에서 제공하는 다중 입출력 시스템 콜입니다.
//   => select()의 사용상의 단점을 보완합니다.  
//      : nfds, readfds, 크기의 한계

#include <poll.h>

// int poll(struct pollfd *fds, nfds_t nfds, int timeout);
// nfds: 등록하고자 하는 배열의 개수

// poll 단점
//  1. 연결이 종료될 때마다, 배열을 직접 관리해야 하는 부담이 있다. => 동적 배열
//  2. 성능?
//   => 관리하고 있는 디스크립터 중에서 이벤트가 발생한 디스크립터를
//      직접 찾아야 한다.

//   => epoll
//     : 이전 버전의 리눅스에서는 사용할 수 없다.
//     : 이벤트가 발생한 디스크립터의 배열을 만들어서 반환한다.
//     => 찾을 필요가 없다.

void print_fds(struct pollfd* fds, int n)
{
	printf("=====================\n");
	printf("n: %d\n", n);
	for (int i = 0 ; i < n ; ++i)
		printf("%5d", fds[i].fd);
	putchar('\n');
	printf("=====================\n");
}

int main()
{
	int ssock = socket(PF_INET, SOCK_STREAM, 0);
	if (ssock == -1)
	{
		perror("socket");
		return -1;
	}

	struct sockaddr_in saddr = {0, };
	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(5000);
	saddr.sin_addr.s_addr = INADDR_ANY;

	int option = 1;
	setsockopt(ssock, SOL_SOCKET, SO_REUSEADDR, &option, sizeof option);

	if (bind(ssock, (struct sockaddr*)&saddr, sizeof saddr) == -1)
	{
		perror("bind");
		return -1;
	}

	if (listen(ssock, SOMAXCONN) == -1)
	{
		perror("listen");
		return -1;
	}

	// 1. 파일 디스크립터 등록
	struct pollfd fds[4096];
	// : 최대 연결의 개수가 1024개 아니다.
	int nfds = 1;
	fds[0].fd = ssock;
	fds[0].events = POLLIN;

	while (1)
	{
		print_fds(fds, nfds);
		int ret = poll(fds, nfds, -1);
		if (ret == 0)
			continue;

		// 연결이 종료되서, 배열을 정리할 필요가 있다.
		int compress = 0;
		for (int i = 0 ; i < nfds ; ++i)
		{
			if (!fds[i].revents & POLLIN)
				continue;

			if (fds[i].fd == ssock)
			{
				// accept
				struct sockaddr_in caddr = {0, };
				caddr.sin_family = AF_INET;
				socklen_t caddrlen = sizeof caddr;
				int csock = accept(ssock, (struct sockaddr*)&caddr, &caddrlen);
				if (csock == -1)
				{
					perror("accept");
					continue;
				}

				fds[nfds].fd = csock;
				fds[nfds].events = POLLIN;
				nfds++;
				printf("new client: %s\n", inet_ntoa(caddr.sin_addr));
			}
			else 
			{
				int csock = fds[i].fd;
				char buf[512];
				int len = read(csock, buf, sizeof buf);
				if (len == 0)
				{
					close(csock);
					fds[i].fd = -1;
					compress = 1;
					continue;
				}
				else if (len == -1)
				{
					perror("read");
					close(csock);
					fds[i].fd = -1;
					compress = 1;
					continue;
				}

				if (write(csock, buf, len) == -1)
				{
					perror("write");
					close(csock);
					fds[i].fd = -1;
					compress = 1;
				}
			}
		} // for

		// compress
		print_fds(fds, nfds);
		if (compress)
		{
			for (int i = 0 ; i < nfds ; ++i)
			{
				if (fds[i].fd == -1)
				{
					for (int j = i; j < nfds -1 ; ++j)
						fds[j] = fds[j+1];

					--i;
					--nfds;
				}
			}
		}
		print_fds(fds, nfds);
	}

	close(ssock);
}
