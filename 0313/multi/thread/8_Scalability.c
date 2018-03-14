
// 확장성
//  : 멀티 코어 시대에서 반드시 고려되어야 하는 것
//   => 더 많은 코어에서 동작할 때, 더 좋은 성능을 내야 한다.
//  => 1억 만들기
#include <sys/time.h>

int timestamp()
{
	struct timeval tv;
	gettimeofday(&tv, 0);

	return tv.tv_sec * 1000 + tv.tv_usec / 1000;
}

#include <unistd.h>
#include <pthread.h>
#include <stdio.h>

#define MAX_THREADS 32

int num_of_threads = 1;
int sum = 0;

void* foo(void* arg)
{
	for (int i = 0 ; i < 50000000 / num_of_threads ; ++i)
	{
		sum += 2;
	}

	return 0;
}

int main()
{
	pthread_t thread[MAX_THREADS];
	
	for (num_of_threads = 1; num_of_threads <= MAX_THREADS; 
			num_of_threads *= 2)
	{
		sum = 0;

		int start = timestamp();
		for (int i = 0 ; i < num_of_threads; ++i)
			pthread_create(&thread[i], 0, &foo, 0);

		for (int i = 0 ; i < num_of_threads; ++i)
			pthread_join(thread[i], 0);
		
		printf("%d threads, result: %d, %d ms\n",
			num_of_threads, sum, timestamp() - start);
	}
}
