#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#include <stdio.h>

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

	struct sockaddr_in caddr = {0, };
	caddr.sin_family = AF_INET;
	socklen_t caddrlen = sizeof caddr;

	// accept: 연결이 수립하고, 데이터를 주고 받기 위한 소켓을 형성한다. 
	int csock = accept(ssock, (struct sockaddr*)&caddr, &caddrlen);
	if (csock == -1)
	{
		perror("accept");
		return -1;
	}

	printf("connected: %s\n", inet_ntoa(caddr.sin_addr));

	// csock을 통해 데이터를 송수신할 수 있다.
	// => read의 처리가 가장 중요합니다.
	//  : 정상적으로 연결이 종료되었는지 여부와 에러로 인해서
	//    연결이 종료되었는지 여부를 구분해서 처리하는 것이 맞습니다.
	 
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

		printf("len: %d\n", len);
	}

	close(csock);
	close(ssock);
}
