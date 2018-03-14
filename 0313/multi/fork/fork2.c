
// fork() 사용시 주의할 점
// => 좀비 프로세스가 발생하는 것을 방지해야 한다.

// 자식 프로세스가 부모 프로세스보다 먼저 종료할 경우
// 자식 프로세스는 자신의 종료 상태값을 부모에게 전달하기 위해
// 자신의 메모리를 바로 해지하지 않는다.
// => 좀비 프로세스
// => 자식의 상태값을 얻어오는 시스템 콜: wait()

// 고아 프로세스: 자식 프로세스보다 부모 프로세스가 먼저
// 종료할 경우 고아 프로세스가 된다.
// => 모든 프로세스의 부모인 init 프로세스가 자식 프로세스에 대해서
//    대신 부모가 되고, 종료한 자식 프로세스에 대해서 wait을
//    호출해 준다.

#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include <stdio.h>
#include <stdlib.h>

int main()
{
	pid_t pid = fork();
	if (pid > 0)
	{
		int status;
		wait(&status);

		printf("status code: %d\n", WEXITSTATUS(status));
	}
	else if (pid == 0)
	{
		sleep(2);
		exit(100);
	}
	else
	{
		perror("fork");
	}
}
