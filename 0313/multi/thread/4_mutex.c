
// 스레드 프로그래밍 장점
//  => 스레드 간 데이터의 공유가 쉽다.
//  => 데이터 레이스 컨디션을 처리해야 한다.

#include <unistd.h>

#include <stdio.h>
#include <pthread.h>

static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void* foo(void* p)
{
	static int x;
	
	for (int i = 0 ; i < 5000 ; ++i)
	{
		pthread_mutex_lock(&mutex);
		x = 100;
		usleep(10);
		x += 1;
		printf("%s: %d\n", (char*)p, x);
		pthread_mutex_unlock(&mutex);
	}
}


int main()
{
	pthread_t thread[3];
	pthread_create(&thread[0], 0, &foo, (void*)"A");
	pthread_create(&thread[1], 0, &foo, (void*)"  B");
	pthread_create(&thread[2], 0, &foo, (void*)"     C");

	for (int i = 0 ; i < 3 ; ++i)
		pthread_join(thread[i], 0);

	printf("program end..\n");
}
