
#include <unistd.h>

#include <stdio.h>

// 1. fork()의 반환값은 2개이다.
//   부모 프로세스: 자식 pid
//   자식 프로세스: 0

// 2. 가상 메모리
//    모든 프로세스는 자신만의 주소 공간을 갖는다.

//  fork() -> sys_fork() -> do_fork() -> copy_process()

int global = 42;
int main()
{
	int n = 30;
	pid_t pid = fork();
	if (pid > 0)
	{
		++global;
		++n;
		printf("부모 프로세스\n");
	}
	else if (pid == 0)
	{
		printf("자식 프로세스\n");
		sleep(1);
		printf("global: %d\n", global);
	}
	else
	{
		perror("fork");
		return -1;
	}

	// printf("after fork..\n");
}
