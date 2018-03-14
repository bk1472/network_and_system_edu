// IP Address: Internet Protocol Address
// => 32Bit
// => : 172.31.30.187 -> 문자열

// bb1e1fac
// inet_addr: IP 문자열을 32비트의 빅 엔디안으로 변환하는 함수. 
// inet_network: IP 문자열을 32비트의 호스트 엔디안으로 변환하는 함수.

// K: manpage
// ctags - 코드 분석 
//   task_struct: g + ]     : tag jump
//                ctrl + t  : back
#include <stdio.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main()
{
	const char* address = "172.31.30.187";
	in_addr_t value = inet_addr(address);

	printf("%x\n", value);

	// inet_addr / inet_network
	// => 인자로 받은 문자열의 주소가 제대로 된 IP 주소인지
	//    확인할 수 있다.
	address = "127.0.0.300";
	value = inet_addr(address);
	if (value == INADDR_NONE)
	{
		fprintf(stderr, "잘못된 IP 주소 입니다. \n");
	}
}
