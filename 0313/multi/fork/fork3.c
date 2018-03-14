#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include <stdio.h>
#include <stdlib.h>

// 자식 프로세스가 종료할 경우, 부모 프로세스에게
// SIGCHLD 라는 시그널을 전송한다.
//  => 비동기적으로 자식의 종료 코드를 수거할 수 있다.
void on_child_exit(int signum)
{
	int status;
	wait(&status);
	printf("child exit code: %d\n", WEXITSTATUS(status));
}

int main()
{
	signal(SIGCHLD, &on_child_exit);

	pid_t pid = fork();
	if (pid > 0)
	{
		for (int i = 0 ; i < 100; ++i)
		{
			usleep(1000000 * 0.5);
			printf("job.....\n");
		}
	}
	else if (pid == 0)
	{
		printf("child created..\n");
		sleep(3);
		exit(100);
	}
	else
	{
		perror("fork");
	}
}
