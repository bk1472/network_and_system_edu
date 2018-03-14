#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#include <stdio.h>

#include "packet.h"

int calculate(char op, int lhs, int rhs)
{
	switch (op)
	{
		case '+': return lhs + rhs;
		case '-': return lhs - rhs;
		case '*': return lhs * rhs;

		default: return -1;
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


	// TCP는 STREAM 이다.
	// => 데이터의 경계가 존재하지 않는다.

	// => TCP를 수신하는 로직이 반드시 작성되어야 한다.
	// : 경계 처리

	// (1):(4):(4)$ 
    // : 비효율적이다.
    //   데이터를 1바이트씩 처리해야 한다.

	// 고정 패킷을 사용한다.
	// : 모든 패킷의 길이가 고정이다.
	//  1. 패킷이 늦게 도착할 경우 문제가 발생한다.
	//  2. 고정 배열로 처리한다면 비효율적이다.

	// 해결 방법
	// 1. 모든 패킷을 전송하기 전에, 패킷의 길이를 전송한다.
	// 2. 패킷이 늦게 수신될 경우를 처리하기 위해서
	//    사용하는 방법: 리차드 스티븐슨
	//   => readn 을 이용하면 된다.


	char buf[9];
	int len;

	int count = 0;
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

		Packet p(buf);
		char op = p.readByte();
		int lhs = p.readInt32();
		int rhs = p.readInt32();
		printf("count(%d), %d %c %d\n", count++, lhs, op, rhs);
		// int result = calculate(op, lhs, rhs);
		// write(csock, &result, sizeof result);
	}

	close(csock);
	close(ssock);
}





