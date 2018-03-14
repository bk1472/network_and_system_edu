#include <stdio.h>
#include <pthread.h>


#include <atomic>
using namespace std;

atomic<int> x;
// x의 모든 연산은 원자적 연산으로 동작한다.

void* foo(void* p)
{
	for (int i = 0 ; i < 100000 ; ++i)
	{
		++x;
	}

	return 0;
}

int main()
{
	pthread_t thread[3];
	for (int i = 0 ; i < 3 ; ++i)
		pthread_create(&thread[i], 0, &foo, 0);

	for (int i = 0 ; i < 3; ++i)
		pthread_join(thread[i], 0);

	printf("x: %d\n", x.load());
}
