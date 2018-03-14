// socket
// connect
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#include <stdio.h>
#include <pthread.h>

// 네트워크 패킷은 비동기적으로 전달된다.
// => 데이터를 수신하는 read를 비동기적으로 처리해 줄 필요가 있다.
void* reader(void* arg)
{
	int csock = (intptr_t)arg;
	char buf[512];

	while (1)
	{
		int len = read(csock, buf, sizeof buf);
		if (len == 0)
			break;
		else if (len == -1)
		{
			perror("read");
			break;
		}

		write(1, buf, len);
	}

	close(csock);
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

	pthread_t thread;
	intptr_t arg = csock;
	pthread_create(&thread, 0, &reader, (void*)arg);

	char buf[512];
	int len;
	while ((len = read(0, buf, sizeof buf)) > 0)
	{
		if (write(csock, buf, len) == -1)
		{
			perror("write");
			break;
		}
	}

	pthread_join(thread, 0);
}
