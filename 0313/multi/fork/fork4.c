#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include <stdio.h>
#include <stdlib.h>

// 자식 프로세스가 종료할 경우, 부모 프로세스에게
// SIGCHLD 라는 시그널을 전송한다.
//  => 비동기적으로 자식의 종료 코드를 수거할 수 있다.

// 문제점 1.
//  => 시그널은 중첩되지 않는다.
//  1. SIGCHLD 핸들러가 수행되는 도중에, SIGCHLD가 또 발생하면
//  다시 수행하지 않는다.
//  2. 여러개의 SIGCHLD가 동시에 발생하더라도, 핸들러는 한번만
//  수행된다.
//  ; 반복문을 통해서 wait을 호출해야 한다.

// 문제점 2.
//  시그널 핸들러 안에서는 절대로 블록되는 함수를 이용하면 안됩니다.
//  => wait이 아닌 waitpid 라는 함수를 통해 처리하는 것이 맞습니다.
void on_child_exit(int signum)
{
	int status;
	// while (wait(&status) != -1)
	while (waitpid(-1, &status, WNOHANG) > 0)
		printf("child exit code: %d\n", WEXITSTATUS(status));
}

int main()
{
	signal(SIGCHLD, &on_child_exit);

	for (int i = 0 ; i < 10 ; ++i)
	{
		pid_t pid = fork();
		if (pid == 0)
		{
			printf("child created...\n");
			if (i < 8)
				sleep(1);
			else
				sleep(3);
			exit(100);
		}
	}

	for (int i = 0 ; i < 1000 ; ++i)
	{
		usleep(1000000 * 0.5);
		printf("job....\n");
	}
}
