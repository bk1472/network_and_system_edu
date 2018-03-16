#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#include <stdio.h>
// epoll: linux 2.6 에서 도입되었습니다.
//   poll => 사용자가 직접 디스크립터 배열을 관리해야 하는 문제
//           사용자가 많아질 수록 성능이 점점 떨어지는 문제

// epoll
//   1. 사용자가 직접 관리하지 않고 사용할 수 있는
//      저장소를 제공한다.
//      epoll의 저장소를 생성해야 한다.
//      epoll_create(size) - deprecated
//      epoll_create1(0)

//   2. 이벤트가 발생하면, (epoll_wait) 함수가 반환하면,
//      이벤트가 발생한 디스크립터 배열을 반환한다.

// 문제점
//    이식성이 조금 떨어질 수 있다. - X

// 고성능 서버의 설계의 핵심
//   => epoll_wait 을 통해 이벤트를 감지하고
//      스레드를 통해 이벤트를 처리한다.
//      스레드 풀: 스레드를 무한정 생성하는 것이 아니라
//          적정 개수의 스레드만 생성해서 관리한다.


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
				event.events = EPOLLIN;
				epoll_ctl(efd, EPOLL_CTL_ADD, csock, &event);
			}
			else
			{
				int csock = revents[i].data.fd;
				char buf[512];
				int len = read(csock, buf, sizeof buf);
				if (len == 0)
				{
					printf("연결이 종료되었습니다. \n");
					close(csock);
					epoll_ctl(efd, EPOLL_CTL_DEL, csock, 0);
					continue;
				}
				else if (len == -1)
				{
					perror("read");
					close(csock);
					epoll_ctl(efd, EPOLL_CTL_DEL, csock, 0);
					continue;
				}

				if (write(csock, buf, len) == -1)
				{
					perror("write");
					close(csock);
					epoll_ctl(efd, EPOLL_CTL_DEL, csock, 0);
				}
			}
		}
	}

	close(ssock);
	close(efd);
}
