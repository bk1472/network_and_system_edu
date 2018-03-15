#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>


#include <sys/select.h>

#include <stdio.h>

// select
//   BSD socket API를 통해 제공됨.
//   가장 오래된 모델
//  => 이식성이 높다.
//  => poll() / epoll()은 리눅스에서만 제공한다.

// fd_set <- bit set

#if 0
int select(int nfds, fd_set *readfds, fd_set *writefds,
		fd_set *exceptfds, struct timeval *timeout);

void FD_CLR(int fd, fd_set *set);
int  FD_ISSET(int fd, fd_set *set);
void FD_SET(int fd, fd_set *set);
void FD_ZERO(fd_set *set);
#endif

// select 한계
// 1. 함수의 설계가 이상하다.
//    nfds: 개수가 아닌, 디스크립터의 최대값 + 1의 의미로 사용된다.
//    감시하고자 등록된 디스크립터 배열의 내용을 변경한다.
//    => 원본 데이터를 별도로 관리하고 있어야 한다.

// 2. fd_set을 사용한다.
//    => 감시할 수 있는 최대 디스크립터의 개수가 1024개이다. 

// 3. 순회를 통해서 이벤트가 발생한 디스크립터를 찾아야 한다.
//    => 최대값이 1024로 설정되는 순간, 매번 비효율적이다.

// ssock: listen socket - accept(read)
// csock: socket        - read
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

	// 1. 감시하고자 하는 디스크립터 등록
	int maxfd;
	fd_set readfds;
	FD_ZERO(&readfds);
	FD_SET(ssock, &readfds);

	maxfd = ssock;
	// nfds: 등록된 디스크립터의 최대값 + 1
	// for (int fd = 0 ; fd < nfds ; ++fd)


	while (1)
	{
		int nfds = maxfd + 1;

		fd_set rreadfds = readfds;
		int ret = select(nfds, &rreadfds, 0, 0, 0);
		if (ret == 0)
			continue;

	
		for (int fd = 0 ; fd < nfds ; ++fd)
		{
			if (!FD_ISSET(fd, &rreadfds))
				continue;

			if (fd == ssock)   
			{
				// 새로운 연결이 들어왔다. - accept
				struct sockaddr_in caddr = {0, };
				caddr.sin_family = AF_INET;
				socklen_t caddrlen = sizeof caddr;
				int csock = accept(ssock, (struct sockaddr*)&caddr, &caddrlen);
				if (csock == -1)
				{
					perror("csock");
					continue;
				}

				// csock을 등록한다.
				FD_SET(csock, &readfds);
				if (csock > maxfd)
					maxfd = csock;

				printf("new client: %s\n", inet_ntoa(caddr.sin_addr));
			}
			else
			{
				// 새로운 데이터가 들어왔다. - read
				int csock = fd;
				char buf[512];
				int len = read(csock, buf, sizeof buf);
				if (len == 0)
				{
					printf("연결이 종료되었습니다.");
					FD_CLR(csock, &readfds);
					close(csock);
					continue;
				}
				else if (len == -1)
				{
					perror("read");
					FD_CLR(csock, &readfds);
					close(csock);
					continue;
				}

				if (write(csock, buf, len) == -1)
				{
					perror("write");
					FD_CLR(csock, &readfds);
					close(csock);
				}
			}
		}
	}

	close(ssock);
}
