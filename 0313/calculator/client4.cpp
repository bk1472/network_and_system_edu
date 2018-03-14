// g++ client4.cpp ./pb/calculator.pb.cc -o client -lprotobuf
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#include <stdio.h>

#include "./pb/calculator.pb.h"


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

	int lhs = 10, rhs = 32;
	char op = '+';
	int i;

	while (scanf("%d%c%d", &lhs, &op, &rhs) == 3)
	{
		Calculator calc;
		calc.set_op(op);
		calc.set_lhs(lhs);
		calc.set_rhs(rhs);
		int len = calc.ByteSize();

		char buf[512];

		short packetlen = htons(len);
		memcpy(buf, &packetlen, sizeof packetlen);
		calc.SerializeToArray(buf + sizeof(packetlen), len);

		write(csock, buf, len + sizeof(packetlen));
	}

	close(csock);
}




















