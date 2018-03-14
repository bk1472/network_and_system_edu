// DNS: Domain Name Server
//   ; 사용자가 IP 주소를 기억하는 것은 어렵다.
//     도메인을 IP 주소로 변환하는 서비스


// naver.com
//   $ nslookup naver.com

// 도메인 구입(.io / :.ai / .cc)
//   : 가비아, whois
//     AWS, Google Domain
#include <unistd.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <stdio.h>

int main(int argc, char* argv[])
{
	if (argc != 2)
		return -1;

	struct hostent* host = gethostbyname(argv[1]);
	if (host == NULL)
	{
		fprintf(stderr, "fail\n");
		return -1;
	}

	for (int i = 0 ; host->h_aliases[i] ; ++i)
		printf("alias: %s\n", host->h_aliases[i]);

	printf("host name: %s\n", host->h_name);
	for (int i = 0 ; host->h_addr_list[i] ; ++i)
	{
		printf("%s\n", 
		inet_ntoa( *(struct in_addr*)host->h_addr_list[i]
		));
	}
}










