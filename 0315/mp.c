#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <stdio.h>

// $ mkfifo myfifo
int main()
{
	int fd = open("myfifo", O_RDWR);
	if (fd == -1)
	{
		perror("open");
		return -1;
	}

	// read는 수신된 내용이 존재하지 않을 경우,
	//  => 블록된다.

	// read는 수신된 내용이 존재할 경우
	//  => 블록되지 않는다.

	// 특정한 파일 디스크립터에 데이터가 수신되었는지 여부를
	// 알 수 있는 시스템 콜을 제공하자.
	//  select
	//  poll
	//  epoll

	char buf[512];
	while (1)
	{
		int len = read(0, buf, sizeof buf);
		buf[len] = '\0';
		printf("keyboard: %s\n", buf);


		len = read(fd, buf, sizeof buf);
		buf[len] = '\0';
		printf("fifo: %s\n", buf);
	}
}





