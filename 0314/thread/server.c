#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#include <stdio.h>
#include <pthread.h>


// 32bit/64bit에 상관없이
// 1. 정수 타입(int)를 포인터로 변환하는 방법.
// 2. 포인터 타입을 정수 타입(int)으로 변환하는 방법.

// intptr_t을 이용하면 됩니다.
void* connection_handler(void* arg)
{
	int csock = (intptr_t)arg;

	char buf[512];
	int len;
	while (1)
	{
		len = read(csock, buf, sizeof buf);
		if (len == 0)
		{
			printf("정상적으로 연결이 종료되었습니다. \n");
			break;
		}
		else if (len == -1)
		{
			perror("read");
			break;
		}

		if (write(csock, buf, len) == -1)
		{
			perror("write");
			break;
		}
	}

	close(csock);
	printf("thread exit...\n");

	return 0;
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


	while (1)
	{
		struct sockaddr_in caddr = {0, };
		caddr.sin_family = AF_INET;
		socklen_t caddrlen = sizeof caddr;
		int csock = accept(ssock, (struct sockaddr*)&caddr, &caddrlen);
		if (csock == -1)
		{
			perror("accept");
			return -1;
		}

		printf("connected: %s\n", inet_ntoa(caddr.sin_addr));

		pthread_t thread;
		intptr_t arg = csock;
		pthread_create(&thread, 0, &connection_handler, (void*)arg);
		pthread_detach(thread);
	}

	close(ssock);
}










