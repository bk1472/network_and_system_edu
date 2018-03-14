// 간단한 브라우져 코드 만들기
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#include <stdio.h>
#include <string.h>

// HTTP Request
//  => Response
//     : status code
//       200:   Success
//       400:   Client Error
//       500:   Server Error

int main()
{
	// 1. socket 만들기 
	int sock = socket(PF_INET,     // Protocol Family Internet
		       SOCK_STREAM, // SOCK_STREAM: TCP / SOCK_DGRAM: UDP
		       0);          // 프로토콜 패밀리의 하위 프로토콜

	// 2. 접속하고자 하는 서비스의 주소 지정
	//   서비스의 주소
	//     컴퓨터 주소: IP Address
	//     프로세스 주소: Port Address
	//      (2byte) 
	//      Well-known Port
	//         SSH, SFTP: 22
	//         HTTP     : 80
	//         HTTPS    : 443
	//         REDIS    : 6379
	//  => 120.50.131.112, 80

	// C 언어에서는 상속이 존재하지 않습니다.
	// 구현하는 방법
	//  1. 공통의 필드
	//  2. 함수에서 반드시 구조체의 크기를 받아야 한다.
	//  : BSD Socket API / GTK
	struct sockaddr_in addr = {0, };
	addr.sin_family = AF_INET;
	addr.sin_port   = htons(80);
	addr.sin_addr.s_addr = inet_addr("120.50.131.112");

	int ret = connect(sock, (struct sockaddr*)&addr, sizeof addr);
	if (ret == -1)
	{
		perror("connect()");
		return -1;
	}

	char buf[512] = "GET /\r\n";
	write(sock, buf, strlen(buf));

	
	int len;
	while ((len = read(sock, buf, sizeof buf)) > 0)
		write(1, buf, len);

	close(sock);
}
