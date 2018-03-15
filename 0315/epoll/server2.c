#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#include <stdio.h>
#include <errno.h>

// select, poll: Level Trigger
// epoll       : Level Trigger, Edge Trigger

// Level Trigger: 수신 버퍼에 데이터가 남아 있다면 반환한다.
//  => 수신 버퍼에 데이터를 일부 남겨 놓을 경우,
//     불필요한 반환이 발생한다.

// Edge  Trigger: 수신 버퍼에 데이터가 도착하는 시점에 반환한다.
//  => 수신 버퍼에 처리할 수 없는 데이터가 남아 있다고 하더라도
//     반환이 발생하지 않는다.
//     : 효율적이다.

// fd = open("a.txt", O_RDONLY | NON_BLOCK);
void set_fd_nonblock(int fd)
{
	// 1. 기존의 파일의 속성을 가져온다.
	int flags = fcntl(fd, F_GETFL, 0);

	// 2. O_NONBLOCK 추가한다.
	flags |= O_NONBLOCK;

	// 3. file이 가지고 있는 속성을 덮어 쓴다.
	fcntl(fd, F_SETFL, flags);
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

	//--------------------
	// 1. epoll 저장소를 생성한다.
	int efd = epoll_create1(0);
	if (efd == -1)
	{
		perror("epoll_create");
		return -1;
	}

#if 0
	typedef union epoll_data {
		void        *ptr;
		int          fd;
		uint32_t     u32;
		uint64_t     u64;
	} epoll_data_t;

	struct epoll_event {
		__u32      events;
		epoll_data data;
	};
#endif
	// 2. 감시하고자 하는 디스크립터를 등록한다.
	struct epoll_event event;
	event.data.fd = ssock;     // data: 사용자가 필요로 하는 정보
	event.events = EPOLLIN;
	epoll_ctl(efd, EPOLL_CTL_ADD, ssock, &event);
	// 등록: EPOLL_CTL_ADD
	// 해지: EPOLL_CTL_DEL

#if 0
       int epoll_wait(int epfd, struct epoll_event *events,
			   int maxevents, int timeout);
#endif
	
	while (1)
	{
		struct epoll_event revents[4096];
		int n = epoll_wait(efd, revents, 4096, -1);
		if (n == 0)
			continue;

		printf("epoll_wait\n");

		// revents 안에는 이벤트가 발생한 디스크립터만4096 존재한다.
		for (int i = 0 ; i < n ; ++i)
		{
			if (revents[i].data.fd == ssock)
			{
				struct sockaddr_in caddr = {0, };
				caddr.sin_family = AF_INET;
				socklen_t csocklen = sizeof caddr;
				int csock = accept(ssock, (struct sockaddr*)&caddr, &csocklen);
				if (csock == -1)
				{
					perror("accept");
					continue;
				}

				struct epoll_event event = {0, };
				event.data.fd = csock;
				// event.events = EPOLLIN;         // Level Trigger
				event.events = EPOLLIN | EPOLLET;  // Edge Trigger

				set_fd_nonblock(csock);
				epoll_ctl(efd, EPOLL_CTL_ADD, csock, &event);
			}
			else
			{
				int csock = revents[i].data.fd;
				char buf[1];   // !!

				//----------------------------------
				// 한번만 데이터를 읽는 것이 아니라, 필요한 만큼
				// 처리할 수 있도록 로직을 변경해야 한다.
				//  => Edge Trigger

				// read를 잘못 사용했을 경우, 
				// 블록되는 문제가 발생한다.
				//  => read를 Non-Blocking 으로 사용해야 한다.

				while (1)
				{
					int len = read(csock, buf, sizeof buf);
					if (len == 0)
					{
						printf("연결이 종료되었습니다. \n");
						close(csock);
						epoll_ctl(efd, EPOLL_CTL_DEL, csock, 0);
						break;
					}
					else if (len == -1)
					{
						// Non Blocking 
						// read: Resource temporarily unavailable
						//  : 수신 버퍼에 데이터가 존재하지 않는다.
						if (errno == EAGAIN)
							break;


						perror("read");
						close(csock);
						epoll_ctl(efd, EPOLL_CTL_DEL, csock, 0);
						break;
					}

					if (write(csock, buf, len) == -1)
					{
						perror("write");
						close(csock);
						epoll_ctl(efd, EPOLL_CTL_DEL, csock, 0);
					}
				}
				//------------------------------------
			}
		}
	}

	close(ssock);
	close(efd);
}
