
// Thread API
//  => OS API
//  => POSIX Thread API
//  => pthread API

// C11 / C++11
//  => OS 독립적인 API를 통해서 스레드를 만들 수 있습니다.

#include <pthread.h>
// 명시적으로 라이브러리를 연결해서 사용해야 합니다.
// $ gcc 1_basic.c -lpthread
#include <stdio.h>

void* foo(void* p)
{
	printf("foo\n");
	printf("%s\n", (char*)p);

	return (void*)0xab;
}

// main의 반환: 프로세스의 종료
// => 프로세스 안에서 동작하는 모든 스레드는 종료된다.

// main thread가 종료하면 프로세스는 종료할까요?
// => 아닙니다.
// pthread_exit(0);
//  : 현재의 스레드를 종료한다.

// 스레드: 경량 프로세스
//  : 프로세스의 컨텍스트 스위칭의 비용보다 훨씬 가볍다.

// 파이버: 유져 모드 스레드
//  Windows 운영체제는 커널 레벨에서 지원한다.
// => Go 언어: 고루틴  

// 1. pthread_create
//    clone(CLONE_VM) -> sys_clone -> do_fork -> copy_process
//   => 메모리에 대한 공유가 된다.

// 2. pthread_join
//   => 좀비 스레드
//   => 스레드의 종료 상태값을 얻어올 수 있다.

// 3. pthread_detach
//   => 생성된 스레드가 종료되면, 스스로 파괴한다.

int main()
{
	pthread_t thread;
	pthread_create(&thread, 0, &foo, (void*)"A");
	// pthread_detach(thread);

	getchar();
	// void* status;
	// pthread_join(thread, &status);
	// printf("status: %p\n", status);

	// pthread_exit(0);
	// 이제는 프로세스 내의 모든 스레드가 종료해야지만
	// 프로세스가 종료한다.
}






