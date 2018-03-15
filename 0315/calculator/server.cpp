#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#include <stdio.h>

#include <future>  // async
//  다른 언어: promise

#include "calculator.pb.h"


// 아래의 구조처럼 되어 있는 라이브러리를 쓰는 것이 좋습니다.
//  => Reactor / Procactor

// C++ 고성능 네트워크 라이브러리
//  => Boost.Asio: 비동기 IO
//       : boost.org
//     Poco Project
//       : pocoproject.org
//  => 클라이언트 / 서버를 만들 때 사용할 수 있습니다.
//     내부의 모든 동작이 비동기로 설계되어 있습니다.
//     accept / read / write 의 동작을 비동기로 사용해야 합니다.


// 동기
// foo() / goo() / hoo();

// foo();
// goo();
// hoo();

// 비동기: 사건의 완료 시점을 알 수 없다.
//   1. 콜백             = Asio
//   2. future / promise

// 문제점
// 1. Callback Hell
// foo([]{
//	goo([]{
//	  hoo([]{

//	  });
//	});
// });
//   : 코드의 가독성이 떨어진다.

// 2. 흐름 제어가 힘들다.
//  foo가 완료하고, goo가 완료된 시점에 hoo를 수행하고 싶다.

// C#, JS - await / coroutine: 비동기 함수를 동기로 처리할 수 있다.
#if 0
{
	await foo();
	await goo();
	await hoo();
}
#endif






ssize_t	readn(int fd, void *vptr, size_t n);

long calculate(int lhs, int rhs, char op)
{
	switch (op)
	{
		case '+': return lhs + rhs;
		case '-': return lhs - rhs;
		case '*': return lhs * rhs;
		case '/': return lhs / rhs;   // rhs != 0
		default:
			return -1;
	}
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

	// 2. 감시하고자 하는 디스크립터를 등록한다.
	struct epoll_event event;
	event.data.fd = ssock;     // data: 사용자가 필요로 하는 정보
	event.events = EPOLLIN;
	epoll_ctl(efd, EPOLL_CTL_ADD, ssock, &event);
	
	while (1)
	{
		struct epoll_event revents[4096];
		int n = epoll_wait(efd, revents, 4096, -1);
		if (n == 0)
			continue;

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
				printf("New connection....\n");
			}
			else
			{
				// async function
				// ----------------------
				auto f = [&] { 
					int csock = revents[i].data.fd;
					char buf[512];
					short packetlen;
					int len = readn(csock, &packetlen, sizeof packetlen);
					if (len == 0)
					{
						printf("1연결이 종료되었습니다. \n");
						close(csock);
						epoll_ctl(efd, EPOLL_CTL_DEL, csock, 0);
						return;
					}
					else if (len == -1)
					{
						perror("readn");
						close(csock);
						epoll_ctl(efd, EPOLL_CTL_DEL, csock, 0);
						return;
					}

					packetlen = ntohs(packetlen);
					printf("packetlen: %d\n", packetlen);
					len = readn(csock, buf, packetlen);
					if (len == 0)
					{
						printf("2연결이 종료되었습니다. \n");
						close(csock);
						epoll_ctl(efd, EPOLL_CTL_DEL, csock, 0);
						return;
					}
					else if (len == -1)
					{
						perror("readn");
						close(csock);
						epoll_ctl(efd, EPOLL_CTL_DEL, csock, 0);
						return;
					}

					Request req;
					req.ParseFromArray(buf, packetlen);

					printf("lhs: %d, rhs: %d, op: %c\n", req.lhs(), req.rhs(), 
							req.op());
					int result = calculate(req.lhs(), req.rhs(), req.op());

					Response res;
					res.set_result(result);
					len = res.ByteSize();
					res.SerializeToArray(buf, len);

					packetlen = htons(len);
					if (write(csock, &packetlen, sizeof packetlen) == -1)
					{
						perror("write");
						return;
					}

					if (write(csock, buf, len) == -1)
					{
						perror("write");
						return;
					}
				};
					
				std::async(std::launch::async, f);
				// f를 비동기로 수행할 수 있습니다.
				// 비동기: 별도의 스레드를 통해 처리한다.
				// 논블록: 대기하지 않는다.
				//-------------------------
			}
		}
	}

	close(ssock);
	close(efd);
}







