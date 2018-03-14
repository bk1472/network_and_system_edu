
// System Call
// 1. Socket을 이용한 Network Programming은 저수준 IO를 이용합니다.
// 2. 저수준 IO
//     : 운영체제 제공하는 API를 직접적으로 이용한다.
//    Windows: Windows API
//    UNIX   : System Call

// 3. Kernel => struct file 
//    : 파일 디스크립터

// 1. Protocol을 처리하는 방법
//  : Google Protocol Buffers
// 2. 서버 다중화
//  : Process / Thread Model(Thread 기술 정리) - Task
//    => Intel TBB
// 3. IO 모델
//  : select / poll / epoll
// 4. 다중화 + IO => Reactor Model


#include <unistd.h>     
// : 가장 위에 쓰는 것이 좋습니다.
// => 이전 버전의 유닉스에서는 반드시 위에 존재해야만 했습니다.

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <stdio.h>

// stdin:  0
// stdout: 1
// stderr: 2

int main()
{
	// manpage
	//  1: shell command
	//  2: system call
	//  3: library
	// 2, K
	int fd = open("test.txt", O_RDONLY);
	printf("fd: %d\n", fd);

	char buf[1024];
	int len = read(fd, buf, sizeof buf);

	// write(STDOUT_FILENO, buf, len);
	write(1, buf, len);
	getchar();

	close(fd);
}











