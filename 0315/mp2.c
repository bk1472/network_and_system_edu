#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <poll.h>

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

	// 1. 감시하고자 하는 디스크립터를 등록한다.
	struct pollfd fds[2];
	fds[0].fd = 0;
	fds[0].events = POLLIN;
	fds[1].fd = fd;
	fds[1].events = POLLIN;

	char buf[512];
	while (1)
	{
		poll(fds, 2, -1); 
		// poll이 반환했다는 것은, 등록된 디스크립터에서
		// 이벤트가 발생하였다.
		//  => 블록없이 데이터를 수신할 수 있다.

		if (fds[0].revents & POLLIN)
		{
			int len = read(0, buf, sizeof buf);
			buf[len] = '\0';
			printf("keyboard: %s\n", buf);
		}

		if (fds[1].revents & POLLIN)
		{
			int len = read(fd, buf, sizeof buf);
			buf[len] = '\0';
			printf("fifo: %s\n", buf);
		}
	}
}





