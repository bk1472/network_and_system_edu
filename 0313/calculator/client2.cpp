#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#include <stdio.h>

#include "packet.h"

#if 0
struct Packet
{
	char* start;
	char* current;

	Packet(char* buf) : start(buf), current(buf) {}

	void writeByte(char v)
	{
		*current = v;	
		current += sizeof v;
	}

	void writeInt32(int v)
	{
		*(int*)current = v;
		current += sizeof v;
	}

	int length()
	{
		return current - start;
	}
};
#endif



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

	// 2*2 => op(1):lhs(4):rhs(4)
	//         '*'   2      2
	int lhs, rhs;
	char op;
	while (scanf("%d%c%d", &lhs, &op, &rhs) == 3)
	{
		printf("%d %c %d\n", lhs, op, rhs);
		
#if 0
		write(csock, &op, sizeof op);
		write(csock, &lhs, sizeof lhs);
		write(csock, &rhs, sizeof rhs);
#endif
		// 하나의 패킷으로 조립해서, write를 한번에 호출하도록 하고 싶다.
		char buf[512];
		// char* p = buf;
		Packet packet(buf);
		packet.writeByte(op);
		packet.writeInt32(lhs);
		packet.writeInt32(rhs);

		int len = packet.length();
		write(csock, buf, len);

		int result;
		len = read(csock, &result, sizeof result);
		if (len == 0)
			break;
		else if (len == -1)
		{
			perror("read");
			break;
		}	

		printf("result: %d\n", result);
	}

	close(csock);
}




















