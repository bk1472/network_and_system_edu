#include <sys/time.h>

// set nopaste
// set paste

int timestamp()
{
	struct timeval tv;
	gettimeofday(&tv, 0);

	return tv.tv_sec * 1000 + tv.tv_usec / 1000;
}

// 확장성
//  : 더 많은 코어에서 동작했을 때, 더 좋은 성능을 가져야 한다.
//    4 core
//     => 8 ~ 16 thread
//     => 가장 좋은 성능을 보여야한다.


// 동기화의 모델이 확장성을 결정하는 것이 아니다.
//  => 프로그래밍 모델
//  => map-reduce model
//     fork-join

// ----
// ----
// ----
// ----
// 락이 존재하면 안된다.

// map: 각각의 스레드가 연산을 수행한다.
// reduce: 각 스레드의 결과를 병합한다.


// 개인용 CPU: i3, i5, i7
//  => 싱글 스레드 성능이 좋다.
// 서버용 CPU: Xeon E5
//  => 멀티 스레드 성능이 좋다.

// 서버 머신
//  : Dell / HP / IBM
#include <unistd.h>
#include <pthread.h>
#include <stdio.h>

#define MAX_THREADS 32

int num_of_threads = 1;
int sum = 0;

// 1 threads, result: 100000000, 141 ms
#if 0
void* foo(void* arg)
{
	for (int i = 0 ; i < 50000000 / num_of_threads ; ++i)
	{
		sum += 2;
	}

	return 0;
}
#endif

// Mutex - push model
#if 0
1 threads, result: 100000000, 902 ms
2 threads, result: 100000000, 3122 ms
4 threads, result: 100000000, 3786 ms
8 threads, result: 100000000, 3411 ms
16 threads, result: 100000000, 3840 ms
32 threads, result: 100000000, 4022 ms
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void* foo(void* arg)
{
	for (int i = 0 ; i < 50000000 / num_of_threads ; ++i)
	{
		pthread_mutex_lock(&mutex);
		sum += 2;
		pthread_mutex_unlock(&mutex);
	}

	return 0;
}
#endif


// Spinlock - pull model
pthread_spinlock_t spinlock;
// 명시적으로 초기화함수를 통해서 초기화해야 한다.
// pthread_spin_init

#if 0
// 경쟁하는 스레드가 많아질 수록 성능이 뮤텍스보다 떨어지는
// 문제가 있습니다.

1 threads, result: 100000000, 485 ms
2 threads, result: 100000000, 1537 ms
4 threads, result: 100000000, 2581 ms
8 threads, result: 100000000, 5289 ms
16 threads, result: 100000000, 8725 ms
32 threads, result: 100000000, 16381 ms

void* foo(void* arg)
{
	for (int i = 0 ; i < 50000000 / num_of_threads ; ++i)
	{
		pthread_spin_lock(&spinlock);
		sum += 2;
		pthread_spin_unlock(&spinlock);
	}

	return 0;
}
#endif

// Atomic Operations
#if 0
1 threads, result: 100000000, 371 ms
2 threads, result: 100000000, 1234 ms
4 threads, result: 100000000, 1455 ms
8 threads, result: 100000000, 1565 ms
16 threads, result: 100000000, 1526 ms
32 threads, result: 100000000, 1521 ms
#endif

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
void* foo(void* arg)
{
	// map
	int local_sum = 0;
	for (int i = 0 ; i < 50000000 / num_of_threads ; ++i)
	{
		// __sync_fetch_and_add(&sum, 2);
		local_sum += 2;
	}

	// reduce
	pthread_mutex_lock(&mutex);
	sum += local_sum;
	pthread_mutex_unlock(&mutex);

	return 0;
}

int main()
{
	// pthread_spin_init(&spinlock, 0);

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
