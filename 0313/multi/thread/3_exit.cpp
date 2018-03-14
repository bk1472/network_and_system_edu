// 스레드의 종료
// => 스레드의 종료 처리


// 스레드의 종료 방법 3가지
// 1. 스레드 함수 반환    -> O
// 2. pthread_exit(0);    -> X
// 3. pthread_cancel();   -> X

// Windows
//  => 객체를 만들었을 때, 객체의 소멸자가 온전하게 호출되는지
//     여부를 검증하는 것이 중요하다.

// => 절대 스레드를 강제로 종료하지 말고,
//    스레드 스스로 반환하도록 만드는 것이 좋다.

#include <unistd.h>
#include <pthread.h>
#include <stdio.h>

struct Resource
{
	Resource()  { printf("Resource\n"); }
	~Resource() { printf("~Resource\n"); }
};

void* foo(void* p)
{
	Resource r;

	printf("foo end\n");
	// pthread_exit(0);
	getchar();
	return 0;
}


int main()
{
	pthread_t thread;
	pthread_create(&thread, 0, &foo, 0);
	sleep(1);
	pthread_cancel(thread);
	// getchar();

	pthread_join(thread, 0);
	printf("program end...\n");
}













