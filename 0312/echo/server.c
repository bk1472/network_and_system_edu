// TCP/IP - BSD API
// 서버를 만드는 방법. 
// 1. socket()
// 2. bind()
// 3. listen()
// 4. accpet() 

// 프로세스가 만들 수 있는 파일의 개수는 한정적이다.
// $ ulimit -a
// $ ulimit -n 20480
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <stdio.h>

// TIME_WAIT
//  => Address already in use
//  => 서버의 포트가 TIME_WAIT 상태에 빠져서, bind 할 수 없다.
//  => TIME_WAIT 역활
//     : 특정 포트에 바인되어 있는 소켓을 바로 해지하는 것이 아니라
//       지연되거나 재전송된 패킷이 연결이 끊긴 이후에도 수신되어서
//       네트워크를 빠져나갈 수 있도록 해준다.

// 서버를 대상으로 TIME_WAIT을 사용하지 않습니다.
//  => 서버를 다시 시작할 수 없다.
//  사용하지 않아도 되는 괜찮은 이유
//  1. 시퀀스 넘버가 마지막 시퀀스 넘버보다 클 경우에만 연결이 수립된다.
//  2. 일반적으로 클라이언트의 포트 번호는 유동적이다. 

// ; 서버는 종료되지 않아야할 뿐 아니라,
//   바로 시작할 수 있어야 한다.
int main()
{
	// ssock: 데이터를 교환하기 위한 목적이 아닌
	//        연결을 수립하기 위한 목적으로 만드는 소켓입니다.
	//  => listen socket
	int ssock = socket(PF_INET, SOCK_STREAM, 0);
	if (ssock == -1)
	{
		perror("socket()");
		return -1;
	}

	// 자신이 연결이 수락할 주소에 대한 정보를 기록한다.
	// => bind
	struct sockaddr_in saddr = {0, };
	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(5000);            

	// 내가 연결을 받을 인터넷 주소(IP 주소)
	// saddr.sin_addr.s_addr = inet_addr("0.0.0.0");
	saddr.sin_addr.s_addr = INADDR_ANY;
	// bind는 실패할 수 있다.
	//  : 클라이언트의 포트는 바뀌지만, 서버의 포트는 변경되지 않는다.

	// listen socket에 대해서는 TIME_WAIT을 비활성화한다.
	int option = 1;
	setsockopt(ssock, SOL_SOCKET, SO_REUSEADDR, &option, sizeof option); 

	if (bind(ssock, (struct sockaddr*)&saddr, sizeof saddr) == -1)
	{
		perror("bind()");
		return -1;
	}

	listen(ssock, SOMAXCONN);

	// 연결이 수립하고, 세션을 형성한다.
	struct sockaddr_in caddr = {0, };
	caddr.sin_family = AF_INET;
	socklen_t csocklen = sizeof caddr;

	accept(ssock, (struct sockaddr*)&caddr, &csocklen);
	printf("connected...%s\n", inet_ntoa(caddr.sin_addr));

	getchar();

	close(ssock);
}
