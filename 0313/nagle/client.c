#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netinet/tcp.h> // TCP_NODELAY

#include <termios.h>     // linux

#include <stdio.h>

static struct termios new, old;
void init_termios(int echo)
{
	tcgetattr(0, &old);
	new = old;
	new.c_lflag &= ~ICANON;
	new.c_lflag &= echo ? ECHO : ~ECHO; 

	tcsetattr(0, TCSANOW, &new);
}

void reset_termios()
{
	tcsetattr(0, TCSANOW, &old);
}

char _getch(int echo)
{
	char ch;

	init_termios(echo);
	ch = getchar();
	reset_termios();

	return ch;
}

char getch()
{
	return _getch(0);
}

char getche()
{
	return _getch(1);
}


// Nagle Algorithm
// : 앞서 전송한 데이터에 대해서 ACK 메세지를 받아야만
//   다음 데이터를 전송하는 알고리즘
// => TCP의 기본 소켓 옵션은 네이글 알고리즘이 활성화되어 있습니다.
//  : TCP_NODELAY 옵션을 활성해주면, 네이글 알고리즘이 적용되지
//    않습니다.
//    setsockopt

int main()
{
#if 1
	int csock = socket(PF_INET, SOCK_STREAM, 0);
	if (csock == -1)
	{
		perror("socket");
		return -1;
	}
	
	struct sockaddr_in saddr = {0, };
	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(5000);
	saddr.sin_addr.s_addr = inet_addr("13.230.244.23");
	
	if (connect(csock, (struct sockaddr*)&saddr, sizeof saddr) == -1)
	{
		perror("connect");
		return -1;
	}
	printf("connected...\n");

	// 네이글 알고리즘 비활성화
	int option = 1;
	setsockopt(csock, IPPROTO_TCP, TCP_NODELAY, &option, sizeof option);

#endif


	char ch;
	while ((ch = getch()) != 'q')
	{
		// printf("ch: %c\n", ch);
		write(csock, &ch, sizeof ch);
	}

	close(csock);
}






