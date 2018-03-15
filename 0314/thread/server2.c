#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#include <stdio.h>
#include <pthread.h>

// 아래 코드는 문제가 있습니다.
// 1. 동기화에 문제가 있습니다.
//   : 멀티 스레드에서 접근 가능한 정적 데이터에대한
//     보호가 필요합니다.
//     pthread_mutex


// 2. 아래의 모델은 Thread per connection 이라고 합니다.
//   => 클라이언트 한개당 별도의 스레드를 생성합니다.
//    1) 엄청나게 많은 스레드가 생성된다.
//    2) 코어의 개수보다 훨씬 많은 스레드가 만들어져
//       대 부분의 스레드는 대기 상태에 있다.
//    3) 실제 로직을 처리하는 부분보다, 컨텍스트 스위칭의
//       CPU의 시간을 더 많이 소모한다.
//    4) 운영체제가 감당할 수 있는 스레드의 개수는 무한하지
//       않다.

// 3. Nginx - Thread Pool Model
//   => 고정 개수의 스레드만 생성한다.
//      비동기의 요청을 처리하는 부분은 운영체제의 API를 이용한다.

//      POSA - 더글라스 슈미트(Reactor / Proactor - ASIO)
//       : ACE 라이브러리
//         C++ Network Programming
//         => Boost.Asio
//            Poco

// Web Server
//   : 정적 리소스
//  => Apache, Nginx(C)

// Web Application Server(WAS)
//   : 동적 리소스

// Apache 초기 버전 모델

struct client
{
	int csock;
	// ...
};


// mutex
static struct client clients[1024];
static int client_count = 0;
static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

// 자료 구조에 락을 사용하고 싶지 않다면
//  => Lock free 자료 구조


// 재귀적 락을 만들면 해결할 수 있다.
//  => lock이 중첩되서 호출되서 데드락의 문제가 발생하는 것을 

// mutex를 두번 이상 잠글 수 있는가?
//  => 리컬시브를 지원하느냐?
void print_clients()
{
	pthread_mutex_lock(&mutex);
	printf("--------------\n");
	for (int i = 0 ; i < client_count; ++i)
		printf("%3d", clients[i].csock);
	putchar('\n');
	printf("--------------\n");
	pthread_mutex_unlock(&mutex);
}

void add_client(int csock)
{
	pthread_mutex_lock(&mutex);
	struct client c = { csock };
	clients[client_count++] = c;
	print_clients();
	pthread_mutex_unlock(&mutex);
}

void remove_client(int csock)
{
	pthread_mutex_lock(&mutex);
	int index;
	for (int i = 0 ; i < client_count ; ++i)
	{
		if (csock == clients[i].csock)
		{
			index = i;
			break;
		}
	}

	if (index >= client_count)
		return;
	
	for (int i = index; i < client_count - 1 ; ++i)
		clients[i] = clients[i+1];
	
	client_count--;
	print_clients();
	pthread_mutex_unlock(&mutex);
}

void broadcast(char* buf, int len)
{
	pthread_mutex_lock(&mutex);
	for (int i = 0 ; i < client_count ; ++i)
	{
		int csock = clients[i].csock;
		write(csock, buf, len);
	}
	pthread_mutex_unlock(&mutex);
}

void* connection_handler(void* arg)
{
	int csock = (intptr_t)arg;
	add_client(csock);

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

		broadcast(buf, len);
#if 0
		if (write(csock, buf, len) == -1)
		{
			perror("write");
			break;
		}
#endif
	}

	remove_client(csock);
	close(csock);
	printf("thread exit...\n");

	return 0;
}

int main()
{
	pthread_mutexattr_t attr = {0, };
	
	pthread_mutexattr_init(&attr);
	pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
	pthread_mutex_init(&mutex, &attr);

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

	while (1)
	{
		struct sockaddr_in caddr = {0, };
		caddr.sin_family = AF_INET;
		socklen_t caddrlen = sizeof caddr;
		int csock = accept(ssock, (struct sockaddr*)&caddr, &caddrlen);
		if (csock == -1)
		{
			perror("accept");
			return -1;
		}

		printf("connected: %s\n", inet_ntoa(caddr.sin_addr));

		pthread_t thread;
		intptr_t arg = csock;
		pthread_create(&thread, 0, &connection_handler, (void*)arg);
		pthread_detach(thread);
	}

	close(ssock);
}










