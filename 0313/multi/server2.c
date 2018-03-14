#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#include <stdio.h>
#include <stdlib.h>

void on_disconnect(int signum)
{
	while (waitpid(-1, NULL, WNOHANG) > 0)
		printf("exit child process\n");
}

// 멀티 프로세스 vs 멀티 스레드
//  장점: 안정적이다.
//  단점: 모든 프로세스는 자신만의 주소 공간을 갖는다.
//     => 브로드캐스팅
//  IPC를 통해서 데이터를 교환해야 하는 번거로움이 있다.
int main()
{
	signal(SIGCHLD, on_disconnect);

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
	while (1)
	{
		int csock = accept(ssock, (struct sockaddr*)&caddr, &caddrlen);
		if (csock == -1)
		{
			perror("accept");
			return -1;
		}

		printf("connected: %s\n", inet_ntoa(caddr.sin_addr));

		pid_t pid = fork();
		if (pid == 0)
		{
			close(ssock); 
			// 자신이 사용하지 않을 파일은 닫는다. 
			// => 참조 계수만 감소한다.

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

				if (write(csock, buf, len) == -1)
				{
					perror("write");
					break;
				}
			}

			close(csock);
			exit(0);
		}
		else if (pid > 0)
		{
			close(csock);
			// 반드시 닫아주어야 합니다.
			// 자식 프로세스가 종료할 때, struct file 구조체가
			// 온전하게 파괴될 수 있습니다.
		}
		else
		{
			perror("fork");
			exit(-1);
		}
	}
	close(ssock);
}
