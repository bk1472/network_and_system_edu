// Error handling
// ./a.out test.txt


#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>        // errno

#include <stdio.h>
#include <string.h>

// 파일의 사이즈를 구하는 프로그램을 작성해보세요.
// $ ./a.out hello.txt
// 42
int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		fprintf(stderr, "argc == 2\n");
		return -1;
	}

	// open -> sys_open

	// DebugView => $err,hr
	// 1. 시스템 콜에서 에러를 처리하는 방법
	//  1) 반환값은 -1 / NULL 입니다.
	//  2) errno를 에러의 원인에 해당하는 번호로 셋팅을 해줍니다.
	//  3) strerror(errno) => 에러의 원인을 문자열로 변경
	//  4) perror() => 현재 에러를 출력하는 기능을 제공한다.
	int fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		// fprintf(stderr, "file open error..\n");
		// printf("errno: %d\n", errno);
		// printf("open(): %s\n", strerror(errno));
		perror("open()");
		return -1;
	}


	// 2. 파일의 처리 - read()
	//   read()
	//   1. 성공할 시, 읽은 바이트 수를 반환합니다.
	//   2. 에러발생시, -1을 반환합니다.
	//   3. EOF에 도달한 경우, 0을 반환합니다. 
	char buf[512];

	int len;
	int fileSize = 0;
	while ((len = read(fd, buf, sizeof buf)) > 0)
	{
		write(1, buf, len);
		fileSize += len;
	}

	printf("size: %d\n", fileSize);

#if 0
	while (1)
	{
		int len = read(fd, buf, sizeof buf);
		if (len <= 0)
			break;

		write(1, buf, len);
	}
#endif

	close(fd);
}









